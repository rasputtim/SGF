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
#ifndef _SGF_Path_h
#define _SGF_Path_h

#include <string>
#include "../SGF_Config.h"
#include "../exceptions/SGF_FileExceptions.h"
#include "SGF_StringUtils.h"

#ifndef _MAX_PATH
    #define MAX_PATH    260
#endif

#ifndef MAX_DRIVE
    #define _MAX_DRIVE   3
#endif

#ifndef MAX_DIR
    #define _MAX_DIR     256
#endif
using namespace std;
namespace SGF {
namespace Filesystem {

/**
 * \class CPath
 *
 * \ingroup SGF_Util
 *
 * \brief Classe Base para Path
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
 class  SGE_API CPath{
    public:
        virtual const string & path() const=0;
        virtual bool isEmpty() const=0;
        virtual bool isFile() const =0;
		virtual bool exist() const =0;
		virtual inline void setPath(const string & s) =0;
		virtual string getType() const = 0;
        virtual ~CPath();
        
        
    protected:
        CPath();
        //CPath(const string & path);
        CPath(const CPath & path);


    };



   class  SGE_API CIllegalPath: public Exception::Filesystem::CException {
    public:
        CIllegalPath(const string & where, int line, const string & file);
        CIllegalPath(const string & where, int line, const Exception::CBase & nested, const string & file);
        virtual ~CIllegalPath() throw();
        CIllegalPath(const CIllegalPath & copy);
        virtual void throwSelf() const {
            throw *this;
        }
    protected:
        virtual Exception::CBase * copy() const {
            return new CIllegalPath(*this);
        }
    };



 /**
 * \class CInsensitivePath
 *
 * \ingroup SGF_Util
 *
 * \brief Classe Path insensível ao tipo de Caixa (alta ou Baixa) dos nomes
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
class  SGE_API CInsensitivePath: public CPath {
    public:
        CInsensitivePath(const CPath & what);
        bool operator==(const CPath & path) const;
		bool isFile() const;
		virtual const string & path() const{return mypath;};
		virtual bool isEmpty() const{return true;};
		virtual bool exist() const {return true;};
		virtual inline void setPath(const string & s) {mypath=s;};
		virtual string getType() const {
        return "insensitive";
		}
private:
		string mypath;
    };

    /* isolated path should not have the leading data directory on it,
	//  The Filesystem will not try to find and complete the path
     */

/**
 * \class CInsensitivePath
 *
 * \ingroup SGF_Util
 *
 * \brief Classe para Caminho (Path) isolado.
 *
 * IsolatedPath não carregam os caminhos completos e o
 * Sistema não vai tentar encontrar o arquivo ou diretório real
 * É apenas uma referência isolada para o programa
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
    class CIsolatedPath: public CPath {
    public:
        explicit CIsolatedPath();
        explicit CIsolatedPath(const string & path);
		explicit CIsolatedPath(const CMyString & path);
        CIsolatedPath(const CIsolatedPath & copy);

        bool operator<(const CIsolatedPath & path) const;
		virtual bool exist() const {return false;};

        virtual const string & path() const;
		virtual CIsolatedPath getDirectory() const;
        virtual CIsolatedPath getFilename() const;
		virtual string getType() const {
        return "isolated";
		}
        CIsolatedPath removeFirstDirectory() const;
        CIsolatedPath firstDirectory() const;

        bool isFile() const;
		virtual bool isEmpty() const;
        virtual inline void setPath(const string & s){ mypath=s;};

		/* a/ + b/ = a/b/ */
        CIsolatedPath join(const CIsolatedPath & path) const;
		CIsolatedPath join(const string & path) const;
        CIsolatedPath & operator=(const CIsolatedPath & copy);

        bool operator==(const CIsolatedPath & path) const;

	private:
		string mypath;

    };


    /* relative path should could or not have the leading data directory on it,
	//  The Filesystem will try to find and complete the path
     */
 /**
 * \class CInsensitivePath
 *
 * \ingroup SGF_Util
 *
 * \brief Classe para Caminho (Path) Relativo.
 *
 * Você inicializa a classe com um caminho qualquer (diretório ou arquivo)
 * A Classe vai tentar achar este caminho no sistema de arquivos real da
 * máquina e vai indicar se o arquivo/caminho existe ou não o se ele está
 * completo (desde a raiz) ou é apenas relativo (ao diretório atual).
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
    class  SGE_API CRelativePath: public CPath {
    public:
        explicit CRelativePath();
        explicit CRelativePath(const string & path, bool findit=true);
        CRelativePath(const CRelativePath & copy);

        bool operator<(const CRelativePath & path) const;
        virtual const string & path() const;
		const string & completePath() const { if(isComplete) return myCompletePath;else return mypath;};
        virtual CRelativePath getDirectory() const;
        virtual CRelativePath getFilename() const;
		virtual string getType() const {
        return "relative";
		}
        CRelativePath removeFirstDirectory() const;
        CRelativePath firstDirectory() const;

        bool isFile() const;
		virtual bool isEmpty() const;
        virtual bool exist() const {return exists;};
		virtual inline void setPath(const string & s){ mypath=s;};
		virtual inline void setCompletedPath(const string & s){ myCompletePath=s;};
        /* a/ + b/ = a/b/ */
        CRelativePath join(const CRelativePath & path) const;
		CRelativePath join(const CIsolatedPath & path) const;
		CRelativePath join(const string & path) const;
        CRelativePath & operator=(const CRelativePath & copy);

        bool operator==(const CRelativePath & path) const;
		bool isComplete;
	private:
		string mypath;
		mutable bool exists;
		string myCompletePath;

    };





 /**
 * \class CAbsolutePath
 *
 * \ingroup SGF_Util
 *
 * \brief Classe para Caminho (Path) Absolutos. Ou seja que começam da raiz.
 *
 * Você inicializa a classe com um caminho completo, ou à partir de uma classe relativa
 * que seja completa
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
	class  SGE_API CAbsolutePath: public CPath{
		public:
        explicit CAbsolutePath();
        explicit CAbsolutePath(const string & path);
        CAbsolutePath(const CAbsolutePath & path);
		CAbsolutePath(const CRelativePath & path);
        CAbsolutePath & operator=(const CAbsolutePath & copy);
		CAbsolutePath & operator=(const CRelativePath & copy);
		CAbsolutePath & copy();
        bool operator<(const CAbsolutePath & path) const;
        bool operator==(const CAbsolutePath & path) const;
        CAbsolutePath removeFirstDirectory() const;
        string firstDirectory() const;
        
		bool isFile() const;
		virtual const string & path() const;
        virtual CAbsolutePath getDirectory() const;
        virtual CAbsolutePath getFilename() const;
		virtual bool isEmpty() const;
        virtual bool exist() const {return exists;};
		virtual inline void setPath(const string & s){ mypath=s;};
        virtual string getType() const {
        return "absolute";
		}
		string getCurrentDir() const {
			return mypath;
		}
        CAbsolutePath join(const CRelativePath & path) const;
		CAbsolutePath join(const CIsolatedPath & path) const;
		CAbsolutePath joinToCurrent(const CRelativePath & path) const;
		CAbsolutePath joinToCurrent(const CIsolatedPath & path) const;
		void localJoin(const CRelativePath &path);
		/* Remove a given path from the start of this path */
        virtual CIsolatedPath remove(const CAbsolutePath & path) const;

		//! retorna o caminho absoluto do diretório onde o sistema está rodando
		inline void GetBasePath(string &path) {
			path=mypath;
		}
		void GetBasePath(char *path);
		inline int GetMaxSize() {
			return tamanho_maximo;
		}

		private:
			//! armazena o caminho em string
			string mypath;
			//string _my_string_complete_path;
			//! armazena o caminho em *char
#ifdef _WIN32
			char _my_dir_prefix[_MAX_DRIVE + _MAX_DIR - 13];
#else
			char _my_dir_prefix[255];  //todo: find equivalente of MAXDRIVE for UNIX
					
#endif
			//char *_my_complete_path;
			int tamanho_maximo;
			mutable bool exists;
    };

} //end Filesystem
} //end SGF

#endif