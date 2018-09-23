#include "util/SGF_FileSystem.h"
#include "util/SGF_Debug.h"
#include "util/SGF_Thread.h"
#include <string>
#include <vector>
#include <map>

#include "sfl.h"
#include "sfldir.h"

using namespace std;
namespace SGF {

namespace Filesystem{

CDirectory::CDirectory(){
}

CDirectory::~CDirectory(){
}

/* Used to signal .. in a path */
class UpDirectory: public std::exception {
public:
    UpDirectory(CAbsolutePath path):
    path(path){
    }

    virtual ~UpDirectory() throw () {
    }

    CAbsolutePath path;
};

class Traverser{
public:
    Traverser(){
    }

    virtual void traverseFile(CDirectory & directory, const string & file) = 0;
    virtual void traverseDirectory(CDirectory & directory, const string & path) = 0;

    virtual ~Traverser(){
    }
};

/* FIXME: this shares a lot of code with findFiles */
vector<CAbsolutePath> CDirectory::findDirectories(const CAbsolutePath & dataPath, const string & find, bool caseInsensitive){
    Util::Thread::ScopedLock scoped(lock);
    vector<CAbsolutePath> out;

    class FindDirectory: public Traverser {
    public:
        FindDirectory():
        failed(false){
        }

        bool failed;
        Util::CReferenceCount<CDirectory> last;

        virtual void traverseFile(CDirectory & directory, const string & file){
            if (directory.directories[file] != NULL){
                last = directory.directories[file];
            }
        }

        virtual void traverseDirectory(CDirectory & directory, const string & path){
            if (directory.directories[path] != NULL){
                last = directory.directories[path];
            } else {
                failed = true;
            }
        }
    };

    FindDirectory lastDirectory;
    traverse(dataPath, lastDirectory);

    if (lastDirectory.failed || lastDirectory.last == NULL){
        return out;
    }

    Debug::debug(Debug::filesystem,__FUNCTION__) << "Search in " << dataPath.path() << " for " << find << endl;
    vector<string> names = lastDirectory.last->directoryNames();
#ifndef USE_ALLEGRO
    for (vector<string>::iterator it = names.begin(); it != names.end(); it++){
        Debug::debug(Debug::filesystem,__FUNCTION__) << "Check if " << *it << " matches " << find << endl;

        //todo: remove file_matches (SFL function)
        if (file_matches(it->c_str(), find.c_str())){
            out.push_back(dataPath.join(CIsolatedPath(*it)));
        }
    }
#endif

    return out;
}

vector<CAbsolutePath> CDirectory::findFiles(const CAbsolutePath & dataPath, const string & find, bool caseInsensitive){
    Util::Thread::ScopedLock scoped(lock);
    vector<CAbsolutePath> out;

    class FindDirectory: public Traverser {
    public:
        FindDirectory():
        failed(false){
        }

        bool failed;
        Util::CReferenceCount<CDirectory> last;

        virtual void traverseFile(CDirectory & directory, const string & file){
            if (directory.directories[file] != NULL){
                last = directory.directories[file];
            }
        }

        virtual void traverseDirectory(CDirectory & directory, const string & path){
            if (directory.directories[path] != NULL){
                last = directory.directories[path];
            } else {
                failed = true;
            }
        }
    };

    FindDirectory lastDirectory;
    traverse(dataPath, lastDirectory);

    if (lastDirectory.failed || lastDirectory.last == NULL){
        return out;
    }

    Debug::debug(Debug::filesystem,__FUNCTION__) << "Search in " << dataPath.path() << " for " << find << endl;
    vector<string> names = lastDirectory.last->filenames();
#ifndef USE_ALLEGRO
    for (vector<string>::iterator it = names.begin(); it != names.end(); it++){
        Debug::debug(Debug::filesystem,__FUNCTION__) << "Check if " << *it << " matches " << find << endl;
        if (file_matches(it->c_str(), find.c_str())){
            out.push_back(dataPath.join(CIsolatedPath(*it)));
        }
    }
#endif

    return out;
}
        
vector<string> CDirectory::directoryNames() const {
    Util::Thread::ScopedLock scoped(lock);
    vector<string> out;

    for (map<string, Util::CReferenceCount<CDirectory> >::const_iterator it = directories.begin(); it != directories.end(); it++){
        if (it->second != NULL){
            out.push_back(it->first);
        }
    }
    
    return out;
}

vector<string> CDirectory::filenames() const {
    Util::Thread::ScopedLock scoped(lock);
    vector<string> out;

    for (map<string, Util::CReferenceCount<Descriptor> >::const_iterator it = files.begin(); it != files.end(); it++){
        if (it->second != NULL){
            out.push_back(it->first);
        }
    }

    for (map<string, Util::CReferenceCount<CDirectory> >::const_iterator it = directories.begin(); it != directories.end(); it++){
        if (it->second != NULL){
            out.push_back(it->first);
        }
    }
    
    return out;
}

void CDirectory::doTraverse(const CAbsolutePath & path, Traverser & traverser){
    if (path.isFile()){
        traverser.traverseFile(*this, path.path());
    } else {
        string name = path.firstDirectory();
        if (name == "."){
            try{
                return doTraverse(path.removeFirstDirectory(), traverser);
            } catch (const UpDirectory & up){
                return doTraverse(up.path, traverser);
            }
        } else if (name == ".."){
            throw UpDirectory(path.removeFirstDirectory());
        }
        traverser.traverseDirectory(*this, path.firstDirectory());
        Util::CReferenceCount<CDirectory> directory = directories[path.firstDirectory()];
        if (directory != NULL){
            try{
                return directory->doTraverse(path.removeFirstDirectory(), traverser);
            } catch (const UpDirectory & up){
                return doTraverse(up.path, traverser);
            }
        }
    }
}

void CDirectory::traverse(const CAbsolutePath & path, Traverser & traverser){
    CAbsolutePath use = path;

    /* The path might contain .. paths that would go out of this directory
     * so just ignore those paths and use the rest of the path.
     */
    while (true){
        try{
            return doTraverse(use, traverser);
        } catch (const UpDirectory & up){
            use = up.path;
        }
    }
}
        
bool CDirectory::exists(const CAbsolutePath & path){
    Util::Thread::ScopedLock scoped(lock);
    class FindIt: public Traverser {
    public:
        FindIt():
        found(false){
        }

        virtual void traverseFile(CDirectory & directory, const string & file){
            if (directory.files[file] != NULL){
                found = true;
            } else if (directory.directories[file] != NULL){
                found = true;
            } else {
                found = false;
            }
        }

        virtual void traverseDirectory(CDirectory & directory, const string & path){
        }

        bool found;
    };

    FindIt find;
    traverse(path, find);
    return find.found;
}

/* Might return NULL if the path can't be found */
Util::CReferenceCount<Descriptor> CDirectory::lookup(const CAbsolutePath & path){
    Util::Thread::ScopedLock scoped(lock);
    class FindIt: public Traverser {
    public:

        virtual void traverseFile(CDirectory & directory, const string & file){
            found = directory.files[file];
        }

        virtual void traverseDirectory(CDirectory & directory, const string & path){
        }

        Util::CReferenceCount<Descriptor> found;
    };

    FindIt find;
    traverse(path, find);
    return find.found;
}

void CDirectory::addFile(const CAbsolutePath & path, const Util::CReferenceCount<Descriptor> & file){
    Util::Thread::ScopedLock scoped(lock);
    class AddPath: public Traverser {
    public:
        AddPath(const Util::CReferenceCount<Descriptor> & file):
        file(file){
        }

        const Util::CReferenceCount<Descriptor> & file;

        virtual void traverseFile(CDirectory & directory, const string & path){
            directory.files[path] = file;
        }

        virtual void traverseDirectory(CDirectory & directory, const string & path){
            if (directory.directories[path] == NULL){
                directory.directories[path] = Util::CReferenceCount<CDirectory>(new CDirectory());
            }
        }
    };

    Debug::debug(Debug::filesystem,__FUNCTION__) << "Add file " << path.path() << endl;
    AddPath adder(file);
    traverse(path, adder);
}
        
void CDirectory::removeFile(const CAbsolutePath & path){
    addFile(path, Util::CReferenceCount<Descriptor>(NULL));
}

}
} //end SGF
