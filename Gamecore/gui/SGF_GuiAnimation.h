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

#ifndef _S_G_F_gui_animation_h
#define _S_G_F_gui_animation_h

#include <vector>
#include <map>
#include <string>

#include "SGF_Coordinate.h"
#include "../util/SGF_Pointer.h"
#include "../graphics/SGF_GradientEffect.h"
#include "../util/SGF_FileSystem.h"
#include "../SGF_Config.h"


namespace SGF{
class CGameFileSystem;
namespace Filesystem{
    class  CAbsolutePath;
}
typedef Filesystem::CAbsolutePath AbsolutePath;

class  CBitmap;
class  SGE_API Token;

namespace Gui{

// To hold images by number easier to access and reuse
typedef map<int, Util::CReferenceCount<CBitmap> > ImageMap;


/**
 * \class CElement
 *
 * \ingroup SGF_Gui
 * 
 * \brief Classe Base para tipos de Frames
 *
 * \author (last to touch it) $Autor: Rasputtim $
 *
 * \version 1.0 $Revision: 1.0 $
 *
 * Contact: raputtim@hotmail.com
 *
 * Created on: 05 de Janeiro de 2012
  */
class  SGE_API CElement{
public:
    virtual ~CElement();
    virtual void act(double xvel, double yvel);
    virtual void draw(int xaxis, int yaxis, const CBitmap &) = 0;
    virtual void draw(const CBitmap &) = 0;
    virtual void reset() = 0;
    virtual void setToEnd(const CRelativePoint &) = 0;
    virtual const string getInfo() = 0;

    virtual inline const CRelativePoint getOffset() const {
        return this->offset;
    }

    virtual inline const CRelativePoint getScrollOffset() const {
        return this->offset;
    }
    
    virtual inline int getTime() const {
        return this->time;
    }

    virtual inline int getAlpha() const {
        return this->alpha;
    }
protected:
    CElement(const Token *);
    CRelativePoint offset;
    CRelativePoint scrollOffset;
    int time;
    int alpha;
private:
    void parseToken(const Token *);
};

/*! Image Frame */
class  SGE_API CImageFrame : public CElement{
public:
    CImageFrame(const Token *, ImageMap &, const string &);
    CImageFrame(Util::CReferenceCount<CBitmap> bmp);
    virtual ~CImageFrame();
    virtual void act(double xvel, double yvel);
    virtual void draw(int xaxis, int yaxis, const CBitmap &);
    virtual void draw(const CBitmap &);
    virtual void reset();
    virtual void setToEnd(const CRelativePoint &);
    virtual const string getInfo();
    virtual inline const Util::CReferenceCount<CBitmap> & getBitmap() const {
        return this->bmp;
    }
protected:
    virtual void parseToken(const Token *, const string &, ImageMap &);

protected:
    Util::CReferenceCount<CBitmap> bmp;
    bool horizontalFlip;
    bool verticalFlip;
};

/*! Text Frame */
class  SGE_API CTextFrame: public CElement {
public:
    CTextFrame(const Token *);
    virtual ~CTextFrame();
    
    virtual void act(double xvel, double yvel);
    virtual void draw(int xaxis, int yaxis, const CBitmap &);
    virtual void draw(const CBitmap &);
    virtual void reset();
    virtual void setToEnd(const CRelativePoint &);
    virtual const string getInfo();
protected:
    virtual void parseToken(const Token *);

    /* FIXME: default this to Globals::DEFAULT_FONT */
    string font;
    string message;
    int fontWidth, fontHeight;
    Effects::Gradient gradient;
};

/* Iterates over a series of items */
class  SGE_API CSequence{
public:
    CSequence();

    virtual Util::CReferenceCount<CElement> getCurrentFrame() const = 0;
    virtual int totalTicks() const = 0;
    virtual void setToEnd() = 0;

    /* Move the sequence along by the number of ticks and at the specified speed
     * Returns true if the sequence can't move any farther.
     */ 
    virtual bool forward(int tickCount, double velocityX, double velocityY) = 0;
    virtual bool reverse(int tickCount, double velocityX, double velocityY) = 0;
    
    virtual void draw(int xaxis, int yaxis, const CBitmap &) = 0;

    virtual void reset() = 0;
    virtual void resetTicks() = 0;

    /* Forcifully move to the next/previous frame */
    virtual void forwardFrame() = 0;
    virtual void backFrame() = 0;

    virtual ~CSequence();
};

class  SGE_API CSequenceFrame: public CSequence {
public:
    CSequenceFrame(const Util::CReferenceCount<CElement> & frame);
    virtual Util::CReferenceCount<CElement> getCurrentFrame() const;

    virtual int totalTicks() const;
    virtual void reset();
    virtual void resetTicks();
    virtual void setToEnd();
    
    virtual void draw(int xaxis, int yaxis, const CBitmap &);

    /* Move the sequence along by the number of ticks and at the specified speed */
    virtual bool forward(int tickCount, double velocityX, double velocityY);
    virtual bool reverse(int tickCount, double velocityX, double velocityY);

    /* Forcifully move to the next/previous frame */
    virtual void forwardFrame();
    virtual void backFrame();

protected:
    Util::CReferenceCount<CElement> frame;
    int ticks;
};

/* Shows sequences in a loop */
class  SGE_API CSequenceLoop: public CSequence {
public:
    CSequenceLoop(int loops);
    
    virtual Util::CReferenceCount<CElement> getCurrentFrame() const;

    virtual void reset();
    virtual void resetTicks();
    virtual void setToEnd();
    virtual void addSequence(const Util::CReferenceCount<CSequence> & sequence);
    virtual void parse(const Token * token, ImageMap & map, const string & baseDir);
    
    virtual void draw(int xaxis, int yaxis, const CBitmap &);
    
    virtual int totalTicks() const;

    /* Move the sequence along by the number of ticks and at the specified speed */
    virtual bool forward(int tickCount, double velocityX, double velocityY);
    virtual bool reverse(int tickCount, double velocityX, double velocityY);

    /* Forcifully move to the next/previous frame */
    virtual void forwardFrame();
    virtual void backFrame();

protected:
    void resetChildrenTicks();
    virtual Util::CReferenceCount<CSequence> getCurrentSequence() const;

    /* The current frame to display */
    unsigned int currentFrame;

    /* The number of times left to loop */
    unsigned int currentLoop;

    /* The total number of times to loop */
    const unsigned int loopTimes;

    vector<Util::CReferenceCount<CSequence> > frames;
};

/* Shows all sequences simaltaneously */
class  SGE_API CSequenceAll: public CSequence {
public:
    CSequenceAll(const Token * token, ImageMap & images, const string & baseDir);
    
    virtual Util::CReferenceCount<CElement> getCurrentFrame() const;

    virtual void reset();
    virtual void resetTicks();
    virtual void setToEnd();
    virtual void addSequence(const Util::CReferenceCount<CSequence> & sequence);
    
    virtual void draw(int xaxis, int yaxis, const CBitmap &);
    
    virtual int totalTicks() const;

    /* Move the sequence along by the number of ticks and at the specified speed */
    virtual bool forward(int tickCount, double velocityX, double velocityY);
    virtual bool reverse(int tickCount, double velocityX, double velocityY);

    /* Forcifully move to the next/previous frame */
    virtual void forwardFrame();
    virtual void backFrame();

protected:
    vector<Util::CReferenceCount<CSequence> > sequences;
    typedef vector<Util::CReferenceCount<CSequence> >::iterator SequenceIterator;
    typedef vector<Util::CReferenceCount<CSequence> >::const_iterator SequenceConstIterator;
};

/* Displays a random child node for its duration */
class  SGE_API CSequenceRandom: public CSequence {
public:
    CSequenceRandom(const Token * token, ImageMap & images, const string & baseDir);
    
    virtual Util::CReferenceCount<CElement> getCurrentFrame() const;

    virtual void reset();
    virtual void resetTicks();
    virtual void setToEnd();
    virtual void addSequence(const Util::CReferenceCount<CSequence> & sequence);
    
    virtual void draw(int xaxis, int yaxis, const CBitmap &);
    
    virtual int totalTicks() const;

    /* Move the sequence along by the number of ticks and at the specified speed */
    virtual bool forward(int tickCount, double velocityX, double velocityY);
    virtual bool reverse(int tickCount, double velocityX, double velocityY);

    /* Forcifully move to the next/previous frame */
    virtual void forwardFrame();
    virtual void backFrame();

protected:
    unsigned int current;
    vector<Util::CReferenceCount<CSequence> > sequences;
    typedef vector<Util::CReferenceCount<CSequence> >::iterator SequenceIterator;
    typedef vector<Util::CReferenceCount<CSequence> >::const_iterator SequenceConstIterator;
};

class  SGE_API CAnimation{
public:
    CAnimation(const Token *token);
    /*! Load only a single bitmap (for backwards compatibility of backgrounds in menu) */
    CAnimation(const string &);
    CAnimation(const AbsolutePath &);
    /*! use an existing bitmap */
    CAnimation(Util::CReferenceCount<CBitmap> image);
    virtual ~CAnimation();
    /*! Reverse with ticks */
    virtual void reverse(int tickCount = 1);
    /*! Forward with ticks */
    virtual void forward(int tickCount = 1);
    /*! Logic ticking per iteration and moving to subsequent frames */
    virtual void act();
    /*! Draw */
    virtual void draw(const CBitmap &);
    virtual void draw(int x, int y, int width, int height, const CBitmap &);
    /*! Forward to next frame with no regard to ticks */
    virtual void forwardFrame();
    /*! Back a frame with no regard to ticks */
    virtual void backFrame();
    /*! Reset everything to the beginning of the start of the animation */
    virtual void resetAll();
    /*! Set everything to the end of the animation */
    virtual void setToEnd();
    /*! Get printable information regarding current frame */
    virtual const string getInfo();

    /*! Reset only frame ticks and other things are ignored */
    virtual void reset();

    /* Total number of ticks used by this animation. If any frames have a time
     * of -1 then the total time will also be -1, meaning infinity.
     */
    virtual int totalTicks() const;

    /*! Return ID */
    virtual inline int getID() const { 
        return id;
    }
    /*! Depth of animation
        TODO make depth unlimited and just use integers for weight of depth
    */
    enum Depth {
        BackgroundBottom,
        BackgroundMiddle,
        BackgroundTop,
        ForegroundBottom,
        ForegroundMiddle,
        ForegroundTop,
    };
    /*! Get depth */
    inline const Depth & getDepth() const { 
        return this->depth;
    }

private:
    int id;
    Depth depth;
    unsigned int currentSequence;
    bool allowReset;
    CRelativePoint axis;
    // This allows the frames to scroll in place
    CRelativePoint velocity;
    CCoordinate window;
    // vector<Util::CReferenceCount<Frame> > frames;
    CSequenceLoop sequence;
    ImageMap images;
};

/*! Generalized to for re-use in other contexts (menu, cutscene, characterselect, etc) */
class  SGE_API CAnimationManager{
public:
    CAnimationManager();
    CAnimationManager(const CAnimationManager &);
    virtual ~CAnimationManager();
    
    const CAnimationManager & operator=(const CAnimationManager &);
    
    void forward(int tickCount = 1);
    void reverse(int tickCount = 1);
    void act();
    void render(const Gui::CAnimation::Depth &, const CBitmap &);
    
    void add(Util::CReferenceCount<Gui::CAnimation > animation);
    
    void reset();
    void setToEnd();

    int totalTicks() const;
    
    const string getInfo(int id, bool all = false);
    
    const vector<int> getIdList();
    
    virtual inline const bool empty() const{
        return this->animations.empty();
    }

virtual inline const int getSize() const {
	 return this->animations.size();
	}
protected:
    int countTicks(const vector<Util::CReferenceCount<Gui::CAnimation> > & toCount) const;

private:
    map< Gui::CAnimation::Depth, vector< Util::CReferenceCount<Gui::CAnimation> > > animations;
};

} //end GUI
} //end SGF
#endif
