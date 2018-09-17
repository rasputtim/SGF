/*
  SGF - Super Game Fabric  Super Game Fabric
  Copyright (C) 2010-2011 Rasputtim <raputtim@hotmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  */

#ifndef _resource_manager_h
#define _resource_manager_h
#include "../SGF_Config.h"
//#include "all.h"

#include <map>
#include <string>
#include <vector>
#include "../util/SGF_FontSystem.h"
#include "../mugen/gc.h"
#include "../util/SGF_Timedif.h"
#include "../util/all_sound.h"
#include "../exceptions/all.h"
#include "../graphics/all.h"
#include "../sprite/all.h"
#include "../util/SGF_Pointer.h"
#include "../gui/all.h"
namespace SGF{

class CSound;
class CBitmap;
class CTTFFont;
class CBitmapFont;
class CFontList;
class CSffSpriteManager;
class CMusic;
namespace Gui {
class CAbsolutePoint;
}

namespace Ast {
class CAstManager;
}
//class Mugen::CMugenFont;

/* Makes the use of the sprite maps easier */
typedef map< string, CSffSpriteManager*> GroupSffManagers;
typedef map< string, GroupSffManagers> PalletizedSffManagerMap;
//! Armazena os sprites, imagens PCX e spritemaps criados à partir de um arquivo ssf
typedef map< string, Mugen::SpriteMap> SffFileSpriteMap;
typedef map< string, SffFileSpriteMap> PalletizedSffFileSpriteMap;

//typedef map<string, CTTFFont *> CTTFFontMap;
//typedef map< unsigned int, CTTFFontMap> CTTFFontSizedMap;

typedef map<string, CBitmapFont *> CBitmapFontMap;
typedef map< unsigned int, CBitmapFontMap> CBitmapFontSizedMap;

typedef map<string, CFont *> FontMap;
typedef map< Gui::CAbsolutePoint, FontMap> FontSizedMap;

typedef map<string, Util::CReferenceCount<CFontInfo> > CFontInfoMap;
typedef map< unsigned int, CFontInfoMap> CFontInfoSizedMap;

typedef map< string, CSndSoundManager *> NamedMugenSoundMap;

enum cacheType{
		cachedSounds,
		cachedMusics,
		cachedDefParsedFiles,
		cachedCMDParsedFiles,
		cachedBitmaps,
		cachedPaths,
		cachedMugenSprites,
		cachedMugenSpriteMaps,
		cachedMugenSffManagers,
	};



/**
 * \class CResource
 *
 * \ingroup SGF_Resources
 *
 * \brief Esta Classe é uma Fábrica de Recursos (bitmaps , sons, sprites, musicas, fontes, etc)
 *
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CResource{
public:
/** mantain a list of the threads with are runing **/
static std::list<Util::Thread::NamedThread> threadList;
	/* poor man's garbage collection.
 * after parsing every pointer stored in this list is checked to see if it
 * is stored in the resulting AST. If the AST does not know about the pointer
 * then no one else does and the pointer should be deleted.
 *
 * void* doesn't work because it doesn't call the destructor. instead use
 * a new class, Collectable, with constructors and fields for every class
 * that is allocated. Collectable will call the appropriate destructor.
 */
static std::list<Ast::CCollectable> saved_pointers;


template<class X>
static void save(const X x){
    saved_pointers.push_back(Ast::CCollectable(x));
}

static void check(){
    if (!(saved_pointers.size() == 0)){
        throw std::exception();
    }
}

/* garbage collection */
static void cleanup(GC::SectionList * list){
    /* pointers that we should keep will be marked true in the map */
    std::map<const void*, bool> marks;

    if (list != 0){
        /* first mark roots */
        marks[list] = true;
        for (GC::SectionList::iterator it = list->begin(); it != list->end(); it++){
            Ast::CSection * section = *it;
            section->mark(marks);
        }
    }

    /* All live objects are now known from the `marks' map. Garbage collection thus
     * means deleting any object that is not in the `marks' map. That is, the set
     * of all objects is AllObjects and all live objects are LiveObjects so
     * the set DeadObjects is just:
     *   DeadObjects = AllObjects - LiveObjects
     * This is a straight-forward computation but actually destroying the DeadObjects
     * is not due to ownership of pointers.
     */

    /* `memory' is a map of objects to the number of times the object was marked.
     * an object could be marked more than once because the following loop
     * will mark every object. if an object is the child of some other object
     * then it (the child) will be marked once itself and once due to the marking
     * of the parent. That is, if the child is A and some object B contains A then
     * the following marks will occur:
     *   mark(A) -> A is marked
     *   mark(B) -> B is marked, then A is marked
     * So A will have a mark count of 2 and B will have a mark count of 1.
     *
     * Each AST node only has one parent so there is no way for A to be live
     * but B to be dead.
     */
    std::map<const void *, int> memory;

    /* all unmarked pointers should be deleted but since the destructors
     * of AST nodes will delete child objects we only need to delete
     * AST nodes that are not the child object of another node.
     * If we mark every single node and add up all the times a node was marked
     * then nodes marked only once will be top-level nodes. Those are the
     * nodes we can destroy safely and ensure the rest of the nodes will
     * die with them.
     *
     * this has worst-case performance of O(N^2). The performance depends on the
     * layout of the tree of AST nodes. For a flat tree like
     *   n - n - n - ...
     * Where all nodes are siblings the performance should be O(n), but if all nodes
     * form a vertical tree then it will be O(n^2)
     *   n
     *   |
     *   n
     *   |
     *   n
     *  ...
     *
     *  One might wonder why nodes destroy their children nodes at all, why not just
     *  let the garbage collector destroy all nodes that haven't been marked as live?
     *  The answer is that the live AST tree that is returned to the game engine
     *  is returned as a single root node. The game engine will delete that node to
     *  destroy the entire tree. If destroying the root node didn't destroy the entire
     *  tree then the game engine would have to get a list of all AST nodes and iterate
     *  through it, destroying all nodes as they came up. I suppose that could be done
     *  but then the parser would have to return a root AST node and an extra data
     *  structure that contained a list of all live nodes (or somehow shove them
     *  into the root AST node). It seems the most elegant solution is to just
     *  make the garbage collector do more work.
     *
     *  Perhaps a more efficient method than this would be if each node knew its parent
     *  then the check for liveness can consist of checking if the node is in
     *  the `marks' map, if not then check if the node is already in some `dead' map,
     *  and if not then find the root of the node, add the root to a to-delete-later
     *  list, and mark all children and parent nodes as dead. In psuedo-code:
     *    check(node):
     *      # Do we know about this node?
     *      if live(node) then return
     *      if dead(node) then return
     *
     *      # Unknown node, so update bookkeeping
     *      make_dead(node)
     *      delete_later(find_root(node))
     *      for each parent_node in node:
     *        make_dead(parent_node)
     *      for each sub_node in node:
     *        make_dead(sub_node)
     *
     *  So lets say we have a vertical tree of depth N and the entire tree is dead.
     *   node1
     *   |
     *   node2
     *  ...
     *   |
     *   nodeN
     *
     *  And the first node we find in the saved_pointers list is node(N/2), i.e the
     *  middle of the tree. We mark all parents as dead (N/2) and children as dead (N/2).
     *  Also assume the root is found while marking parents, so that doesn't incur an
     *  extra cost. Total work for one marking the middle node is N. Looking at all other
     *  nodes takes N time, but for each node they are already marked as dead so work
     *  per node is 1.
     *
     *  Total work is 2N for a vertical tree.
     *
     *  Currently, AST nodes do not keep track of their parents. If garbage collection
     *  is a bottle-neck then this algorithm should be implemented.
     */
    for (std::list<Ast::CCollectable>::iterator it = saved_pointers.begin(); it != saved_pointers.end(); it++){
        Ast::CCollectable & collect = *it;

        /* anything already marked in the `marks' map is a live object so we should
         * not consider it here.
         */
        if (! marks[collect.pointer()]){
            std::map<const void *, bool> temp;
            collect.mark(temp);

            /* merge marks into the total count */
            for (std::map<const void *, bool>::iterator mit = temp.begin(); mit != temp.end(); mit++){
                memory[mit->first] += 1;
            }
        }
    }

    /* finally destroy the nodes with no parents */
    for (std::list<Ast::CCollectable>::iterator it = saved_pointers.begin(); it != saved_pointers.end(); it++){
        Ast::CCollectable & collect = *it;

        /* a mark count of 1 signifies objects with no parents */
        if (memory[collect.pointer()] == 1){
            collect.destroy();
        }
    }
    // std::cout << "Destroying everything" << std::endl;
    saved_pointers.clear();
}


    /* do not prepend Util::getDataPath() to paths. Resource will do it for you.
     */
    static CBitmap * getBitmap(const string & path) throw (Exception::Filesystem::CNotFound);
	static CBitmap * getBitmap(const Filesystem::CAbsolutePath &path) throw (Exception::Filesystem::CNotFound);
	static CBitmap * getBitmap(const Filesystem::CRelativePath &path) throw (Exception::Filesystem::CNotFound);
	//Path Methods
	// Todo : Deprecated after new CPath definition
	static Filesystem::CAbsolutePath & getPath(const string & file) throw (Exception::Filesystem::CNotFound);//;
	static Filesystem::CAbsolutePath & getPath(char &file);
	static Filesystem::CAbsolutePath & getPath(Filesystem::CAbsolutePath &path) throw (Exception::Filesystem::CNotFound);
	static Filesystem::CAbsolutePath & getPath(Filesystem::CRelativePath &path) throw (Exception::Filesystem::CNotFound);

	/** \brief retorna uma fonte que não se sabe o tipo
	* \param name: nome da fonte (caminho da fonte)
	* \param width: largura da fonte
	* \param height: altura da fonte
	*/
	static const CFont & getFont(const string & name, int width, int height);//;

	static CTTFFont * getDefaultFont();
	static CTTFFont * getDefaultFont(int x,int y);

	static CTTFFont * getTTFont(const string & path, int width, int height) throw (Exception::Filesystem::CNotFound);//;
	//static CTTFFont * getTTFont(const string & path, int ptsize) throw (Exception::Filesystem::CNotFound);//;
	//static Mugen::CMugenFont * getMugenFont(const string & path, int width, int height);
	static CBitmapFont * getBitmapFont(const string & path, int width, int height) throw (Exception::Filesystem::CNotFound);

	//  Sprites
	static CSffSpriteManager * getSffSpriteManager(const Filesystem::CAbsolutePath & filename,const Filesystem::CAbsolutePath & palette,bool mask );
	static Mugen::SpriteMap getMugenSpriteMap(const SGF::Filesystem::CAbsolutePath &filename, bool mask, const SGF::Filesystem::CAbsolutePath & palette);
	static void getMugenSpriteMap(const SGF::Filesystem::CAbsolutePath & filename, const SGF::Filesystem::CAbsolutePath & palette, SGF::Mugen::SpriteMap & sprites, bool mask);
	static Util::CReferenceCount<CMugenSprite> getMugenSprite(const SGF::Filesystem::CAbsolutePath &filename, int groupNumber, int spriteNumber, bool mask, const SGF::Filesystem::CAbsolutePath & palette=SGF::Filesystem::CAbsolutePath());

	// Parsed Files
	static Util::CReferenceCount<Ast::CAstManager> getDEFParsedFile(const Filesystem::CAbsolutePath & path);
	static Util::CReferenceCount<Ast::CAstManager> getCMDParsedFile(const Filesystem::CAbsolutePath & path);
	static Util::CReferenceCount<Ast::CAstManager> getCOMParsedFile(const Filesystem::CAbsolutePath & path);
	static Util::CReferenceCount<Ast::CAstManager> getAIRParsedFile(const Filesystem::CAbsolutePath & path);
	static Util::CReferenceCount<Ast::CAstManager> getCMDParsedString(const string & path);


	static CMusic * getMusic(const Filesystem::CRelativePath & path);
	static Util::CSmartPtr_MT<CMusic> getMusic(const Filesystem::CAbsolutePath & path);
	static list<Ast::CSection*> * copy(list<Ast::CSection*> * input);
   //New ones to implement
   /* do not prepend Util::getDataPath() to paths. Resource will do it for you.
     */
    static CSound * getSound(const Filesystem::CRelativePath & path) throw (Exception::Filesystem::CNotFound);
    static CSound * getSound(const string & path)throw (Exception::Filesystem::CNotFound);

	static void getMugenSounds(const string & filename, MugenSoundMap & m_sounds);


private:
	Util::Thread::LockObject my_lockcmd;
	Util::Thread::LockObject my_lockdef;
	Util::Thread::LockObject my_lockair;
	static int getCacheSize(cacheType cache);
	friend class CCollector;
	CResource();
    virtual ~CResource();
    // New One to implement
	CSound * _getSound(const Filesystem::CAbsolutePath & path) throw (Exception::Filesystem::CNotFound);
    CBitmap * _getBitmap(const Filesystem::CAbsolutePath & path) throw (Exception::Filesystem::CNotFound);
	CSound * _getSound(const string & path);
    CBitmap * _getBitmap(const string & path) throw (Exception::Filesystem::CNotFound);
	//CTTFFont * _getTTFont(const string & path, unsigned int ptsize);
	CFont * _getTTFont(const string & file,int width , int height);
//	Mugen::CMugenFont * _getMugenFont(const string & path, int width, int height);
	CFont * _getBitmapFont(const string & path, int width, int height);
	Filesystem::CAbsolutePath & _getPath(const string & file) throw (Exception::Filesystem::CNotFound);
	CSffSpriteManager * _getSffSpriteManager(const Filesystem::CAbsolutePath & filename,const Filesystem::CAbsolutePath & palette,bool mask);
	Mugen::SpriteMap _getMugenSpriteMap(const SGF::Filesystem::CAbsolutePath &filename, bool mask, const SGF::Filesystem::CAbsolutePath & palette);
	void _getMugenSpriteMap(const SGF::Filesystem::CAbsolutePath & filename, const SGF::Filesystem::CAbsolutePath & palette, SGF::Mugen::SpriteMap & sprites, bool mask);

	Util::CReferenceCount<CMugenSprite> _getMugenSprite(const SGF::Filesystem::CAbsolutePath &filename, int groupNumber, int spriteNumber, bool mask, const SGF::Filesystem::CAbsolutePath & palette);


	const CFont & _getFont(const string & path, int width, int height) const throw (Exception::Filesystem::CNotFound);

    Util::CReferenceCount<Ast::CAstManager> _getDEFParsedFile(const Filesystem::CAbsolutePath & path);
	Util::CReferenceCount<Ast::CAstManager> _getCMDParsedFile(const Filesystem::CAbsolutePath & path);
	Util::CReferenceCount<Ast::CAstManager> _getCOMParsedFile(const Filesystem::CAbsolutePath & path);
	Util::CReferenceCount<Ast::CAstManager> _getAIRParsedFile(const Filesystem::CAbsolutePath & path);

	Util::CReferenceCount<Ast::CAstManager> _getCMDParsedString(const string & path);

	CMusic * _getMusic(const Filesystem::CRelativePath & path);
	Util::CSmartPtr_MT<CMusic> _getMusic(const Filesystem::CAbsolutePath & path);

	void _getMugenSounds(const string & filename, MugenSoundMap & m_sounds);



private:
	// para inicializar o singleton
    static CResource * my_resource;
   	map<string, CSound*> my_sounds;
    map<string, CBitmap*> my_bitmaps;
	map<string, Filesystem::CAbsolutePath*> my_files;
	//=== Mugen Sprites ===============
	PalletizedSffManagerMap my_sffSpriteMans;
	PalletizedSffFileSpriteMap my_MugenSpritemaps;
	PalletizedSffFileSpriteMap my_MugenBitmaps;
	//==== CTTFFontSizedMap ttfsizedfonts;
	FontSizedMap my_sizedfonts;
	//====  Mugen Parsed Files ========
	map<string, Ast::CAstManager*> my_defParses;
	map<string, Ast::CAstManager*> my_comParses;

	//=======  MUSIC AND SOUND ========
	Util::CSmartPtr_MT<CMusic> my_musicInstance;
	NamedMugenSoundMap my_mugenSounds;
	//============Get sizes================
	int getsize(cacheType type) {
		switch(type) {
		case	cachedSounds: return my_sounds.size(); break;
		case	cachedMusics: return 10; break;
		//case	cachedDefParsedFiles: return my_defParses.size(); break;
		//case	cachedCMDParsedFiles: return my_comParses.size(); break;
		case	cachedBitmaps: return my_bitmaps.size(); break;
		case	cachedPaths: return my_files.size(); break;
		case	cachedMugenSprites: return my_MugenBitmaps.size(); break;
		case	cachedMugenSpriteMaps: return my_MugenSpritemaps.size(); break;
		case	cachedMugenSffManagers: return my_sffSpriteMans.size(); break;
		default: return 10;
	}



	}


	// CResource cache size control. Try to control the ammount of memory used by CResources
	struct ResourcesControl{
		ResourcesControl():
		max_sounds(getCacheSize(cachedSounds)),
		max_musics(getCacheSize(cachedMusics)),
		max_defParses(getCacheSize(cachedDefParsedFiles)),
		max_comParses(getCacheSize(cachedCMDParsedFiles)),
		max_bitmaps(getCacheSize(cachedBitmaps)),
		max_paths(getCacheSize(cachedPaths)),
		max_mugenSprites(getCacheSize(cachedMugenSprites)),
		max_mugenSpriteMaps(getCacheSize(cachedMugenSpriteMaps)),
		max_mugensSffManagers(getCacheSize(cachedMugenSffManagers))
		{};

		int max_sounds;
		int max_musics;
		int max_defParses;
		int max_comParses;
		int max_bitmaps;
		int max_paths;
		int max_mugenSprites;
		int max_mugenSpriteMaps;
		int max_mugensSffManagers;

	};

	ResourcesControl my_cacheControl;
};
} //end SGF
#endif
