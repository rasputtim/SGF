#ifndef _gui_select_list_h
#define _gui_select_list_h

#include <string>
#include <vector>

#include "SGF_Coordinate.h"
#include "../util/SGF_Pointer.h"
namespace SGF{
class CFont;

namespace Gui{

/*! Select Item pure virtual interface */
class CSelectItem{
public:
    CSelectItem();
    virtual ~CSelectItem();
    
    virtual void draw(int x, int y, int width, int height, const CBitmap &, const CFont &) const = 0;
    virtual bool isEmpty() const = 0;
};

/*! Select List Interface */
class CSelectListInterface{
public:
    CSelectListInterface();
    virtual ~CSelectListInterface();

    //! Logic
    virtual void act() = 0;

    //! Render
    virtual void render(const CBitmap &, const CFont &) const = 0;

    //! Add item
    virtual void addItem(const Util::CReferenceCount<CSelectItem> &) = 0;

    //! Add vector of items
    virtual void addItems(const vector<Util::CReferenceCount<CSelectItem> > &) = 0;
    
    //! Get vector of items
    virtual const vector<Util::CReferenceCount<CSelectItem> > & getItems() const = 0;
    
    //! Get specific item
    virtual const Util::CReferenceCount<CSelectItem> getItem(unsigned int index) const = 0;
    
    //! Get specific item
    virtual const Util::CReferenceCount<CSelectItem> getItemByCursor(unsigned int index) const = 0;
    
    virtual void clearItems() = 0;
    
    virtual void setCellDimensions(int width, int height) = 0;
    virtual void setCellSpacing(int x, int y) = 0;
    virtual void setCellMargins(int x, int y) = 0;
    virtual void setStartingOffset(int x, int y) = 0;
    
    virtual void setCursors(int total) = 0;
    virtual int totalCursors() const = 0;
    
    enum CursorState{
        Disabled,
        Active,
        Done,
        Invalid,
    };

    /* Get the location in pixels of an item where it would be drawn */
    virtual void getDrawLocation(const Util::CReferenceCount<CSelectItem> & item, int * x, int * y) const = 0;
    
    virtual void setCurrentIndex(unsigned int cursor, unsigned int location) = 0;
    virtual unsigned int getCurrentIndex(unsigned int cursor) const = 0;
    virtual void setCurrentState(unsigned int cursor, const CursorState &) = 0;
    virtual const CursorState getCurrentState(unsigned int cursor) const = 0;
    virtual bool up(unsigned int cursor) = 0;
    virtual bool down(unsigned int cursor) = 0;
    virtual bool left(unsigned int cursor) = 0;
    virtual bool right(unsigned int cursor) = 0;
    
    //! Has more low/high
    virtual bool hasMoreLow() const = 0;
    virtual bool hasMoreHigh() const = 0;
    
    //! Get dimensions
    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    
    //! Access Empty
    virtual inline void setAccessEmpty(bool access){
        this->accessEmpty = access;
    }
    //! Get Occupy empty
    virtual inline bool getAccessEmpty() const {
        return this->accessEmpty;
    }
    
    //! Draw Empty
    virtual inline void setDrawEmpty(bool draw){
        this->drawEmpty = draw;
    }
    //! Get Draw empty
    virtual inline bool getDrawEmpty() const {
        return this->drawEmpty;
    }
    
    //! Set wrap
    virtual inline void setWrap(bool wrap){
        this->allowWrap = wrap;
    }
    //! Get wrap
    virtual inline bool getWrap() const {
        return this->allowWrap;
    }
    
protected:
    
    //! Can occupy empty cells/spaces
    bool accessEmpty;
    
    //! Can draw empty cells
    bool drawEmpty;
    
    //! Is wrappable
    bool allowWrap;
};

/*! CCursor handler */
class CCursor{
public:
    CCursor(unsigned int index, const CSelectListInterface::CursorState &);
    ~CCursor();
    CCursor(const CCursor &);
    const CCursor & operator=(const CCursor &);
    void setIndex(unsigned int index);
    unsigned int getIndex() const;
    void increment();
    void decrement();
    void setState(const CSelectListInterface::CursorState &);
    const CSelectListInterface::CursorState & getState() const;
private:
    unsigned int index;
    CSelectListInterface::CursorState state;
};

/*! Simple list */
class CSimpleSelect: public CSelectListInterface {
public:
    CSimpleSelect();
    virtual ~CSimpleSelect();
    
    virtual void act();
    virtual void render(const CBitmap &, const CFont &) const;
    virtual void addItem(const Util::CReferenceCount<CSelectItem> &);
    virtual void addItems(const vector<Util::CReferenceCount<CSelectItem> > &);
    virtual const vector<Util::CReferenceCount<CSelectItem> > & getItems() const;
    virtual const Util::CReferenceCount<CSelectItem> getItem(unsigned int index) const;
    virtual const Util::CReferenceCount<CSelectItem> getItemByCursor(unsigned int cursor) const;
    virtual void clearItems();
    virtual void setCellDimensions(int width, int height);
    virtual void setCellSpacing(int x, int y);
    virtual void setCellMargins(int x, int y);
    virtual void setStartingOffset(int x, int y);
    virtual void setCursors(int total);
    virtual int totalCursors() const;
    virtual void setCurrentIndex(unsigned int cursor, unsigned int location);
    virtual unsigned int getCurrentIndex(unsigned int cursor) const;
    virtual void setCurrentState(unsigned int cursor, const CSelectListInterface::CursorState &);
    virtual const CSelectListInterface::CursorState getCurrentState(unsigned int cursor) const;
    virtual void getDrawLocation(const Util::CReferenceCount<CSelectItem> & item, int * x, int * y) const;
    virtual bool up(unsigned int cursor);
    virtual bool down(unsigned int cursor);
    virtual bool left(unsigned int cursor);
    virtual bool right(unsigned int cursor);
    
    virtual bool hasMoreLow() const;
    virtual bool hasMoreHigh() const;
    
    virtual int getWidth();
    virtual int getHeight();
    
    virtual void setViewable(unsigned int viewable){
        this->viewable = viewable;
    }
    virtual unsigned int getViewable() const {
        return this->viewable;
    }
    
    enum Layout {
        Vertical,
        Horizontal,
    };
    
    virtual void setLayout(const Layout & layout){
        this->layout = layout;
    }
    virtual const Layout & getLayout() const {
        return this->layout;
    }
    
    
    virtual void setScrollOffset(int offset){
        this->scrollOffset = offset;
    }
    virtual int getScrollOffset() const {
        return this->scrollOffset;
    }
    
protected:
    bool checkCursor(unsigned int cursor) const;
    void calculateLeft(unsigned int cursor);
    void calculateRight(unsigned int cursor);
    Layout layout;
    unsigned int viewable;
    unsigned int currentTop;
    int scrollOffset;
    int cellWidth, cellHeight;
    int cellSpacingX, cellSpacingY;
    int cellMarginX, cellMarginY;
    int startOffsetX, startOffsetY;
    vector<CCursor> cursors;
    vector<Util::CReferenceCount<CSelectItem> > items;
};

/*! Select Grid */
class CGridSelect: public CSelectListInterface {
public:
    CGridSelect();
    virtual ~CGridSelect();
    
    virtual void act();
    virtual void render(const CBitmap &, const CFont &) const;
    virtual void addItem(const Util::CReferenceCount<CSelectItem> &);
    virtual void addItems(const vector<Util::CReferenceCount<CSelectItem> > &);
    virtual const vector<Util::CReferenceCount<CSelectItem> > & getItems() const;
    virtual const Util::CReferenceCount<CSelectItem> getItem(unsigned int index) const;
    virtual const Util::CReferenceCount<CSelectItem> getItemByCursor(unsigned int cursor) const;
    virtual void clearItems();
    virtual void setCellDimensions(int width, int height);
    virtual void setCellSpacing(int x, int y);
    virtual void setCellMargins(int x, int y);
    virtual void setStartingOffset(int x, int y);
    virtual void setCursors(int total);
    virtual int totalCursors() const;
    virtual void setCurrentIndex(unsigned int cursor, unsigned int location);
    virtual unsigned int getCurrentIndex(unsigned int cursor) const;
    virtual void setCurrentState(unsigned int cursor, const CSelectListInterface::CursorState &);
    virtual const CSelectListInterface::CursorState getCurrentState(unsigned int cursor) const;
    virtual void getDrawLocation(const Util::CReferenceCount<CSelectItem> & item, int * x, int * y) const;
    virtual bool up(unsigned int cursor);
    virtual bool down(unsigned int cursor);
    virtual bool left(unsigned int cursor);
    virtual bool right(unsigned int cursor);
    
    virtual bool hasMoreLow() const;
    virtual bool hasMoreHigh() const;
    
    virtual int getWidth();
    virtual int getHeight();
    
    enum Layout {
        Static,
        InfiniteHorizontal,
        InfiniteVertical,
    };
    
    virtual void setLayout(const Layout & layout){
        this->layout = layout;
    }
    virtual const Layout & getLayout() const {
        return this->layout;
    }
    
    virtual void setGridSize(int x, int y){
        this->gridX = x;
        this->gridY = y;
    }
    virtual const int getGridX() const {
        return this->gridX;
    }
    virtual const int getGridY() const {
        return this->gridY;
    }
    
protected:
    bool moveUp(unsigned int cursor);
    bool moveDown(unsigned int cursor);
    bool moveLeft(unsigned int cursor);
    bool moveRight(unsigned int cursor);

    bool checkCursor(unsigned int cursor) const;
    
    Layout layout;
    int gridX, gridY;
    int cellWidth, cellHeight;
    int cellSpacingX, cellSpacingY;
    int cellMarginX, cellMarginY;
    int startOffsetX, startOffsetY;
    unsigned int offset;
    vector<CCursor> cursors;
    vector<Util::CReferenceCount<CSelectItem> > items;
};

}
} //end SGF
#endif
