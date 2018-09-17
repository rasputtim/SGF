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
#ifndef _SGF__util_referencecounting_h
#define _SGF__util_referencecounting_h

#include "../SGF_Config.h"

namespace SGF{
namespace Util{

/* Some helpful pointer classes, probably equivalent to stuff in boost
http://www.linuxprogrammingblog.com/cpp-objects-reference-counting
 */
	/* Não é necessário se preocupar em deletar o objeto na classe que utiliza CReferenceCount.
	O próprio default destrutor da classe apaga o objeto */
/* multithreading
http://www.informit.com/articles/article.aspx?p=31529&seqNum=13
To check: http://www.codeproject.com/KB/cpp/auto_ref.aspx
http://www.multicorewinsoft.com/thread_ptr.html
http://csc.lsu.edu/~kosmas/smartPointers.html
*/


/**
 * \class CLockingProxy
 *
 * \ingroup SGF_Util
 *
 * \brief Trava de um Ponteiro inteligente
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \note sintaxe:  template <> vector<int> Parameter<int>::stack;
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
template <class Data>
class CLockingProxy
{
public:
   CLockingProxy(Data* pObj) : pointee_ (pObj)
   { pointee_->Lock(); }
   ~CLockingProxy()
   { pointee_->Unlock(); }
   Data* operator->() const
   { return pointee_; }
private:
   CLockingProxy& operator=(const CLockingProxy&);
   Data* pointee_;
};


/**
 * \class CSmartPtr_MT
 *
 * \ingroup SGF_Util
 *
 * \brief Implementa um ponteiro inteligente Multithread
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \note sintaxe:  template <> vector<int> Parameter<int>::stack;
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
template <class Data>
class  SGE_API CSmartPtr_MT{
public:
    CSmartPtr_MT(Data * what = NULL):
    count(NULL),
    pointee_(what){
        count = new int;
        *count = 1;
    }

    CSmartPtr_MT(const CSmartPtr_MT<Data> & him){
        pointee_ = him.pointee_;
        count = him.count;
        *count += 1;
    }
   CSmartPtr_MT & operator=(Data * what){
        release();
        count = new int;
        *count = 1;
        pointee_ = what;
        return *this;
    }
    CSmartPtr_MT & operator=(const CSmartPtr_MT<Data> & him){
       /* this object might have a link to `him' so if we release first
         * then `him' will get deleted before we can capture his data.
         * we need to increase his count first and then release our data
         * to insure that `him' will still be alive.
         */
		int * temp_count = him.count;
        *temp_count += 1;
        Data * temp_data = him.pointee_;
        release();
        pointee_ = temp_data;
        count = temp_count;
		 return *this;
    }
	/* use this if you need to convert between classes in a heirarchy.
     * Base
     * Child: public Base
     * ReferenceCount<Base> base;
     * ReferenceCount<Child> child;
     * base = child; is illegal but
     * base = child.convert<Base>(); is ok
     */

	/* THIS VERSION CAUSES MEMORY LEAK
    template <class Convert>
    CSmartPtr_MT<Convert> convert() const {
        CSmartPtr_MT<Convert> what;
        what.count = count;
        *what.count += 1;
        what.pointee_ = (Convert*) pointee_;
        return what;
    }
	*/
	template <class Convert>
    operator  CSmartPtr_MT<Convert>() const {
         CSmartPtr_MT<Convert> out;
        out.release();
        out.pointee_ = (Convert*) this->pointee_;
        out.count = this->count;
        *out.count += 1;
        return out;
    }

	CLockingProxy<Data> operator->() const
	{
	   return CLockingProxy<Data>(pointee_);
	}

	 bool operator!() const {
        return !this->pointee_;
    }

    Data & operator*() const {
        return *pointee_;
    }
	 /* get the raw pointer -- be ultra careful! */
    Data * raw() const {
        return pointee_;
    }
	bool operator<(const CSmartPtr_MT<Data> & him) const {
        return pointee_ < him.pointee_;
    }
    bool operator==(const CSmartPtr_MT<Data> & him) const {
        return pointee_ == him.pointee_;
    }

    bool operator!=(const CSmartPtr_MT<Data> & him) const {
        return !(*this == him);
    }

    bool operator==(const void * what) const {
        return pointee_ == what;
    }

    bool operator!=(const void * what) const {
        return !(*this == what);
    }

    virtual ~CSmartPtr_MT(){
		release();
    }
	//like release, but without deleting the object. witch will be deleted another place
	//! be ultra carefull with this method
	virtual void clear(){
		*count=1;
		pointee_ = NULL;
	}
public:

    void release(){
        *count -= 1;
        if (*count == 0){
            delete pointee_;
            delete count;
            pointee_ = NULL;
            count = NULL;
        }
    }
	/* this has to be public to make the convert() function work but pretend
     * its private!
     */
public:
    int * count;
    Data * pointee_;
};


/**
 * \class CReferenceCount
 *
 * \ingroup SGF_Util
 *
 * \brief Implementa um ponteiro inteligente Sem segurança Multithread
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \note sintaxe:  template <> vector<int> Parameter<int>::stack;
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
template <class Data>
class  SGE_API CReferenceCount{
public:
    CReferenceCount(Data * what = NULL):
    count(NULL),
    data(what){
        count = new int;
        *count = 1;
    }

    CReferenceCount(const CReferenceCount<Data> & him){
        data = him.data;
        count = him.count;
        *count += 1;
    }
   CReferenceCount & operator=(Data * what){
        release();
        count = new int;
        *count = 1;
        data = what;
        return *this;
    }
    CReferenceCount & operator=(const CReferenceCount<Data> & him){
       /* this object might have a link to `him' so if we release first
         * then `him' will get deleted before we can capture his data.
         * we need to increase his count first and then release our data
         * to insure that `him' will still be alive.
         */
		int * temp_count = him.count;
        *temp_count += 1;
        Data * temp_data = him.data;
        release();
        data = temp_data;
        count = temp_count;
		 return *this;
    }
	/* use this if you need to convert between classes in a heirarchy.
     * Base
     * Child: public Base
     * ReferenceCount<Base> base;
     * ReferenceCount<Child> child;
     * base = child; is illegal but
     * base = child.convert<Base>(); is ok
     */
	/* this versionof convert causes memory leak
    template <class Convert>
    CReferenceCount<Convert> convert() const {
        CReferenceCount<Convert> what;
        what.count = count;
        *what.count += 1;
        what.data = (Convert*) data;
        return what;
    }
	*/
	template <class Convert>
    operator CReferenceCount<Convert>() const {
        CReferenceCount<Convert> out;
        out.release();
        out.data = (Convert*) this->data;
        out.count = this->count;
        *out.count += 1;
        return out;
    }
	 bool operator!() const {
        return !this->data;
    }
    Data * operator->() const {
        return data;
    }

    Data & operator*() const {
        return *data;
    }
	 /* get the raw pointer -- be ultra careful! */
    Data * raw() const {
        return data;
    }
	bool operator<(const CReferenceCount<Data> & him) const {
        return data < him.data;
    }
    bool operator==(const CReferenceCount<Data> & him) const {
        return data == him.data;
    }

    bool operator!=(const CReferenceCount<Data> & him) const {
        return !(*this == him);
    }

    bool operator==(const void * what) const {
        return data == what;
    }

    bool operator!=(const void * what) const {
        return !(*this == what);
    }

    virtual ~CReferenceCount(){
		release();
    }

public:

    void release(){
        *count -= 1;
        if (*count == 0){
            if (data) {delete data;
			data= NULL;
			}
            if (data) {
				delete count;
				count = NULL;
			}

        }
    }
	/* this has to be public to make the convert() function work but pretend
     * its private!
     */

    int * count;
    Data * data;
};


/**
 * \class CPointerToObject
 *
 * \ingroup SGF_Util
 *
 * \brief Implementa um ponteiro inteligente Sem segurança Multithread nem Contador de referências
 *
 * \note Inicializa seu ponteiro para NULL e deleta o dado apontado no seu destrutor
  * how is this different from the CReferenceCount class above? its basically
 * the same thing but only allows one owner at a time.
*
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \note sintaxe:  template <> vector<int> Parameter<int>::stack;
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 04 de Janeiro de 2012
 */
template <class Data>
class  SGE_API CPointerToObject{
public:
    CPointerToObject():
        data(NULL){
        }

    CPointerToObject(Data * him):
    data(him){
    }

    CPointerToObject & operator=(Data * him){
        if (data != NULL){
            delete data;
        }

        data = him;
        return *this;
    }

    Data & operator*() const {
        return *data;
    }
	 /* get the raw pointer -- be ultra careful! */
    Data * raw() const {
        return data;
    }
    bool operator==(const void * what) const {
        return data == what;
    }

    bool operator!=(const void * what) const {
        return !(*this == what);
    }

    Data* operator->() const {
        return data;
    }

    virtual ~CPointerToObject(){
        delete data;
    }

private:
    Data* data;
};

} //end namespace Util
} //end namespace SGF
#endif
