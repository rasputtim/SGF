#include "gui/SGF_GuiAnimation.h"

#include <stdio.h>
#include <vector>
#include <math.h>
#include <sstream>
#include "util/SGF_Token.h"
#include "graphics/SGF_TransBitmap.h"
#include "graphics/SGF_Bitmap.h"
//#include "util/stretch-bitmap.h"
#include "util/SGF_FontSystem.h"
//#include "globals.h"
#include "graphics/SGF_GradientEffect.h"
#include "util/SGF_Debug.h"
#include "util/SGF_Util.h"
#include "util/SGF_FileSystem.h"
#include "exceptions/all.h"

using namespace std;
using namespace std;
namespace SGF{

using namespace Gui;
static Uint8 clamp(Uint8 in, Uint8 low = 0, Uint8 high = 255){
    return static_cast<Uint8>(Util::clamp(static_cast<int>(in),static_cast<int>(low),static_cast<int>(high)));
}
// Temporary solution
static void renderSprite(const CBitmap & bmp, const int x, const int y, const int alpha, const bool hflip, const bool vflip, const CBitmap & work){
   Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN"<<  endl;
   Debug::debug(Debug::gui,__FUNCTION__) << "[From CBitmap: "<<&bmp<<" ] - (x,y) ("<<x<<" , "<<y<<" )"<<  endl;
   Debug::debug(Debug::gui,__FUNCTION__) << "[Tom CBitmap: "<<&work<<" ] - (x,y) ("<<x<<" , "<<y<<" )"<<  endl;
   Debug::debug(Debug::gui,__FUNCTION__) << "[Alpha: "<<alpha <<" ] [hflip: "<<hflip<<" ] "<<" ] [vflip: "<<vflip<<" ] "<<  endl;
   bmp.setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
   if (alpha != 255){
        CBitmap::transBlender( 0, 0, 0, alpha );
        if (hflip && !vflip){
            bmp.translucent().drawHFlip(x,y, work);
        } else if (!hflip && vflip){
            bmp.translucent().drawVFlip(x,y, work);
        } else if (hflip && vflip){
            bmp.translucent().drawHVFlip(x,y, work);
        } else if (!hflip && !vflip){
            bmp.translucent().draw(x,y, work);
        }
    } else {
        if (hflip && !vflip){
            bmp.drawHFlip(x,y,NULL, work);
        } else if (!hflip && vflip){
            bmp.drawVFlip(x,y, NULL,work);
        } else if (hflip && vflip){
            bmp.drawHVFlip(x,y, NULL,work);
        } else if (!hflip && !vflip){
            bmp.draw(x,y,NULL, work);
        }
    }
   //retorna para o bitmap mode anterior
   bmp.setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);
   Debug::debug(Debug::gui,__FUNCTION__) << "END"<<  endl;

}

CElement::CElement(const Token * token):
time(50),
alpha(255){
    if (token != NULL){
        TokenView view = token->view();
        while (view.hasMore()){
            try{
                const Token * tok;
                view >> tok;
                parseToken(tok);
            } catch ( const CTokenException & ex ) {
                throw CLoadException(__FILE__, __LINE__, ex, "Gui::CAnimation::CElement parse error");
            } catch ( const CLoadException & ex ) {
                throw ex;
            }
        }
    }
}

CElement::~CElement(){
}

void CElement::parseToken(const Token * token){
    if (*token == "alpha"){
        // get alpha
        token->view() >> alpha;
    } else if (*token == "offset"){
        // Get the offset location it defaults to 0,0
        double x=0, y=0;
        try {
            token->view() >> x >> y;
        } catch (const CTokenException & ex){
        }
        offset.set(x,y);
    } else if (*token == "time"){
        // time to display
        token->view() >> time;
    } else {
        Debug::debug(Debug::menu,__FUNCTION__) << "Unhandled Gui::CAnimation::CElement attribute: " << endl;
       // if (Global::getDebug() >= 3){
       //     token->print(" ");
       // }
    }
}

void CElement::act(double xvel, double yvel){
    scrollOffset.moveBy(xvel, yvel);
}

CImageFrame::CImageFrame(const Token *the_token, ImageMap &images, const string & baseDir):
CElement(the_token),
bmp(NULL),
horizontalFlip(false),
verticalFlip(false){
	Debug::debug(Debug::menu,__FUNCTION__) << "INITIALIZING  IMAGEFRAME "<< endl;
    /*
    if (*the_token != "frame"){
        throw CLoadException(__FILE__, __LINE__, "Not an frame");
    }
    */
    /* The usual setup of an animation frame is
    // use image -1 to not draw anything, it can be used to get a blinking effect
    (frame (image NUM) (alpha NUM) (offset x y) (hflip 0|1) (vflip 0|1) (time NUM))
    */
    TokenView view = the_token->view();
    while (view.hasMore()){
        try{
            const Token * token;
            view >> token;
            parseToken(token, baseDir, images);
        } catch ( const CTokenException & ex ) {
            throw CLoadException(__FILE__, __LINE__, ex, "Menu animation parse error");
        } catch ( const CLoadException & ex ) {
            throw ex;
        }
    }
}

void CImageFrame::parseToken(const Token * token, const string & baseDir, ImageMap & images){
    if (*token == "image"){
        // get the number
        string maybeNumber;
        token->view() >> maybeNumber;
			Debug::debug(Debug::menu,__FUNCTION__) << "LOAD IMAGE: "<< maybeNumber<< endl;
        if (Util::matchRegex(maybeNumber, Util::CRegex("\\d+"))){
            int num;
            token->view() >> num;
            if (images.find(num) == images.end()){
                ostringstream out;
                out << "No image for index " << num;
                throw CLoadException(__FILE__, __LINE__, out.str());
            }
            // now assign the bitmap
            bmp = images[num];
        } else {
			Filesystem::CAbsolutePath caminhox = Filesystem::getInstance().find(Filesystem::CRelativePath(baseDir + "/" + maybeNumber));
			

            bmp = Util::CReferenceCount<CBitmap>(new CBitmap(caminhox.path()));
        }
    } else if (*token == "hflip"){
        // horizontal flip
        token->view() >> horizontalFlip;
    } else if (*token == "vflip"){
        // horizontal flip
        token->view() >> verticalFlip;
    } else {
		Debug::debug(Debug::menu,__FUNCTION__) << "Unhandled Gui::CAnimation::CImageFrame attribute: " << token->getName()<<endl;
//        if (Global::getDebug() >= 3){
    //        token->print(" ");
    //    }
    }
}

CImageFrame::CImageFrame(Util::CReferenceCount<CBitmap> bmp):
CElement(NULL),
bmp(bmp),
horizontalFlip(false),
verticalFlip(false){
    time = -1;
}

CImageFrame::~CImageFrame(){
}

static bool closeFloat(double a, double b){
    const double epsilon = 0.001;
    return fabs(a-b) < epsilon;
}

void CImageFrame::act(double xvel, double yvel){
    scrollOffset.moveBy(xvel, yvel);
    if (bmp != NULL){
        if (scrollOffset.getDistanceFromCenterX() >= bmp->getWidth()){
            scrollOffset.setX(0);
        } else if (scrollOffset.getDistanceFromCenterX() <= -(bmp->getWidth())){
            scrollOffset.setX(0);
        }
        if (scrollOffset.getDistanceFromCenterY() >= bmp->getHeight()){
            scrollOffset.setY(0);
        } else if (scrollOffset.getDistanceFromCenterY() <= -(bmp->getHeight())){
            scrollOffset.setY(0);
        }
    }
}

void CImageFrame::draw(const int xaxis, const int yaxis, const CBitmap & work){
    Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN / [CBitmap: "<< &work <<" ](x,y) =>"<< xaxis << " , " << yaxis<< endl;
	if (!bmp){
        return;
    }

    if (!closeFloat(scrollOffset.getDistanceFromCenterX(), 0) || !closeFloat(scrollOffset.getDistanceFromCenterY(), 0)){
		bmp->setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
        // Lets do some scrolling
        // CBitmap temp = CBitmap::temporaryBitmap(bmp->getWidth(), bmp->getHeight());
        //AnimationPoint loc;
        CAbsolutePoint loc;
        if (scrollOffset.getRelativeX() < 0){
            loc.setX(scrollOffset.getDistanceFromCenterX() + bmp->getWidth());
        } else if (scrollOffset.getRelativeX() > 0){
            loc.setX(scrollOffset.getDistanceFromCenterX() - bmp->getWidth());
        }
        if (scrollOffset.getRelativeY() < 0){
            loc.setY(scrollOffset.getDistanceFromCenterY() + bmp->getHeight());
        } else if (scrollOffset.getRelativeY() > 0){
            loc.setY(scrollOffset.getDistanceFromCenterY() - bmp->getHeight());
        }

        /*
        bmp->Blit((int) scrollOffset.getDistanceFromCenterX(), (int) scrollOffset.getDistanceFromCenterY(), temp);
        bmp->Blit((int) scrollOffset.getDistanceFromCenterX(), (int) loc.getY(), temp);
        bmp->Blit((int) loc.getX(), (int) scrollOffset.getDistanceFromCenterY(), temp);
        bmp->Blit((int) loc.getX(), (int) loc.getY(), temp);

        renderSprite(temp, (int)(xaxis+offset.getDistanceFromCenterX()), (int)(yaxis+offset.getDistanceFromCenterY()), alpha, horizontalFlip, verticalFlip, work);
        */

        double x = xaxis+offset.getDistanceFromCenterX();
        double y = yaxis+offset.getDistanceFromCenterY();

        renderSprite(*bmp,
                    (int)(x + scrollOffset.getDistanceFromCenterX()),
                    (int)(y + scrollOffset.getDistanceFromCenterY()),
                    alpha, horizontalFlip, verticalFlip, work);

        renderSprite(*bmp,
                    (int)(x + loc.getX()),
                    (int)(y + scrollOffset.getDistanceFromCenterY()),
                    alpha, horizontalFlip, verticalFlip, work);

        renderSprite(*bmp,
                    (int)(x + scrollOffset.getDistanceFromCenterX()),
                    (int)(y + loc.getY()),
                    alpha, horizontalFlip, verticalFlip, work);

        renderSprite(*bmp,
                    (int)(x + loc.getX()),
                    (int)(y + loc.getY()),
                    alpha, horizontalFlip, verticalFlip, work);

    bmp->setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);
    } else {
		Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN Render Sprite "<<  endl;
		bmp->setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
        renderSprite(*bmp, (int)(xaxis+offset.getDistanceFromCenterX()), (int)(yaxis+offset.getDistanceFromCenterY()), alpha, horizontalFlip, verticalFlip, work);
		bmp->setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);
		Debug::debug(Debug::gui,__FUNCTION__) << "END Rendering Sprite "<<  endl;

	}
}

/* This is mainly called from select-list to draw the cells. I'm not sure
 * of the utility of stretching the bitmap to fit the cell dimensions. Most
 * likely the cell will contain an image and the image will be the same
 * size as the cell.
 */
void CImageFrame::draw(const CBitmap & work){
    bmp->setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
	//const CBitmap & temp = CBitmap::temporaryBitmap(bmp->getWidth(), bmp->getHeight());
    //temp.clearToMask();
    //renderSprite(*bmp, 0, 0, alpha, horizontalFlip, verticalFlip, temp);


	renderSprite(*bmp, 0, 0, alpha, horizontalFlip, verticalFlip, work);

	//s    temp.drawStretched(work);
    bmp->setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);
    /* FIXME: This should work, but it doesn't.. */
    /*
    Graphics::StretchedBitmap show(bmp->getWidth(), bmp->getHeight(), work);
    show.start();
    renderSprite(*bmp, 0, 0, alpha, horizontalFlip, verticalFlip, show);
    show.finish();
    */
}

void CImageFrame::reset(){
    scrollOffset = CRelativePoint();
}

void CImageFrame::setToEnd(const CRelativePoint & end){
    scrollOffset = end;
}

static const char * FRAME_TEXT = "Offset: ( %f, %f)\nScroll Offset: ( %f, %f)\nTime: %d\nHorizontal Flip: %d\nVertical Flip: %d\nAlpha: %d\n\n";

const string CImageFrame::getInfo(){
    char info[255];
    std::sprintf(info, FRAME_TEXT, offset.getRelativeX(), offset.getRelativeY(), scrollOffset.getRelativeX(), scrollOffset.getRelativeY(), time, horizontalFlip, verticalFlip, alpha);
    return string(info);
}

CTextFrame::CTextFrame(const Token *token):
CElement(token),
fontWidth(20),
fontHeight(20){
    TokenView view = token->view();
    while (view.hasMore()){
        try{
            const Token * token;
            view >> token;
            parseToken(token);
        } catch ( const CTokenException & ex ) {
            throw CLoadException(__FILE__, __LINE__, ex, "Menu animation parse error");
        } catch ( const CLoadException & ex ) {
            throw ex;
        }
    }
}

CTextFrame::~CTextFrame(){
}

void CTextFrame::act(double xvel, double yvel){
    gradient.forward();
    CElement::act(xvel, yvel);
}

static const CFont & getFont(const string & font, int width, int height){
    if (font != ""){
        return CFont::getFont(Filesystem::CRelativePath(font), width, height);
    }

    return CFont::getDefaultFont(width, height);
}

void CTextFrame::draw(int xaxis, int yaxis, const CBitmap & work){
    double x = xaxis + offset.getDistanceFromCenterX() + scrollOffset.getDistanceFromCenterX();
    double y = yaxis + offset.getDistanceFromCenterY() + scrollOffset.getDistanceFromCenterY();

    const CFont & font = getFont(this->font, fontWidth, fontHeight);
    font.drawText((int) x, (int) y, gradient.current_intcolor(), work, "%s", 0, message.c_str());
}

void CTextFrame::draw(const CBitmap & work){
    /* Probably don't need this.. but implement it if you do! */
}

void CTextFrame::reset(){
    scrollOffset = CRelativePoint();
}

void CTextFrame::setToEnd(const CRelativePoint & point){
    scrollOffset = point;
}

const string CTextFrame::getInfo(){
    return message;
}

void CTextFrame::parseToken(const Token * token){
    if (*token == "message"){
        token->view() >> message;
    } else if (*token == "font"){
        TokenView view = token->view();
        view >> font;
        try{
            view >> fontWidth >> fontHeight;
        } catch (const CTokenException & ignore){
        }
        if (fontWidth < 1){
            fontWidth = 1;
        }
        if (fontHeight < 1){
            fontHeight = 1;
        }
    } else if (*token == "color"){
        int red, green, blue;
        token->view() >> red >> green >> blue;
		Colors::ColorDefinition tempColor = {clamp(red),clamp(green),clamp(blue),255};
        gradient = Effects::Gradient(tempColor);
    } else if (*token == "gradient"){
        gradient = Effects::Gradient(token);
    }
}

CSequence::CSequence(){
}

CSequence::~CSequence(){
}

CSequenceFrame::CSequenceFrame(const Util::CReferenceCount<CElement> & frame):
frame(frame),
ticks(0){
}

void CSequenceFrame::draw(int xaxis, int yaxis, const CBitmap & work){
    frame->draw(xaxis, yaxis, work);
}

Util::CReferenceCount<CElement> CSequenceFrame::getCurrentFrame() const {
    return frame;
}

int CSequenceFrame::totalTicks() const {
    return frame->getTime();
}

void CSequenceFrame::setToEnd(){
    ticks = frame->getTime();
}

bool CSequenceFrame::forward(int tickCount, double velocityX, double velocityY){
    frame->act(tickCount * velocityX, tickCount * velocityY);
    ticks += tickCount;
    return ticks > frame->getTime();
}

bool CSequenceFrame::reverse(int tickCount, double velocityX, double velocityY){
    frame->act(-tickCount * velocityX, -tickCount * velocityY);
    ticks -= tickCount;
    return ticks < 0;
}

void CSequenceFrame::forwardFrame(){
    /* nop */
}

void CSequenceFrame::backFrame(){
    /* nop */
}

void CSequenceFrame::reset(){
    ticks = 0;
    frame->reset();
}

void CSequenceFrame::resetTicks(){
    ticks = 0;
}

CSequenceLoop::CSequenceLoop(int loops):
currentFrame(0),
currentLoop(loops),
loopTimes(loops){
}

Util::CReferenceCount<CElement> CSequenceLoop::getCurrentFrame() const {
    if (currentFrame < frames.size()){
        return frames[currentFrame]->getCurrentFrame();
    } else {
        /* Return the last frame */
        if (frames.size() > 0){
            return frames[frames.size() - 1]->getCurrentFrame();
        }
    }
    return Util::CReferenceCount<CElement>(NULL);
}

Util::CReferenceCount<CSequence> CSequenceLoop::getCurrentSequence() const {
    if (currentFrame < frames.size()){
        return frames[currentFrame];
    } else {
        /* Return the last frame */
        if (frames.size() > 0){
            return frames[frames.size() - 1];
        }
    }
    return Util::CReferenceCount<CSequence>(NULL);

}

void CSequenceLoop::draw(int xaxis, int yaxis, const CBitmap & work){
    Util::CReferenceCount<CSequence> current = getCurrentSequence();
    if (current != NULL){
        current->draw(xaxis, yaxis, work);
    }
}

void CSequenceLoop::reset(){
    currentFrame = 0;
    currentLoop = loopTimes;
    for (vector<Util::CReferenceCount<CSequence> >::iterator it = frames.begin(); it != frames.end(); it++){
        Util::CReferenceCount<CSequence> & sequence = *it;
        sequence->reset();
    }
}

/* Does the same thing as reset except for calling resetTicks on children nodes */
void CSequenceLoop::resetTicks(){
    currentFrame = 0;
    currentLoop = loopTimes;
    for (vector<Util::CReferenceCount<CSequence> >::iterator it = frames.begin(); it != frames.end(); it++){
        Util::CReferenceCount<CSequence> & sequence = *it;
        sequence->resetTicks();
    }
}

/* Similar to resetTicks but doesn't reset the current frame or loop */
void CSequenceLoop::resetChildrenTicks(){
    for (vector<Util::CReferenceCount<CSequence> >::iterator it = frames.begin(); it != frames.end(); it++){
        Util::CReferenceCount<CSequence> & sequence = *it;
        sequence->resetTicks();
    }
}

void CSequenceLoop::setToEnd(){
    /* FIXME */
}

void CSequenceLoop::addSequence(const Util::CReferenceCount<CSequence> & sequence){
    frames.push_back(sequence);
}

static Util::CReferenceCount<CSequence> parseSequence(const Token * token, ImageMap & images, const string & baseDir){
    if (*token == "frame"){
        Util::CReferenceCount<CElement> frame(new CImageFrame(token, images, baseDir));
        return Util::CReferenceCount<CSequence>(new CSequenceFrame(frame));
    } else if (*token == "text"){
        Util::CReferenceCount<CElement> frame(new CTextFrame(token));
        return Util::CReferenceCount<CSequence>(new CSequenceFrame(frame));
    } else if (*token == "loop"){
        int times;
        token->view() >> times;
        Util::CReferenceCount<CSequenceLoop> loop(new CSequenceLoop(times));
        loop->parse(token, images, baseDir);
        return loop;
    } else if (*token == "all"){
        return Util::CReferenceCount<CSequence>(new CSequenceAll(token, images, baseDir));
    } else if (*token == "random"){
        return Util::CReferenceCount<CSequence>(new CSequenceRandom(token, images, baseDir));
    }

    return Util::CReferenceCount<CSequence>(NULL);
}

void CSequenceLoop::parse(const Token * token, ImageMap & images, const string & baseDir){
    TokenView view = token->view();
    /* first ignore the number of times to loop */
    int ignore;
    view >> ignore;

    while (view.hasMore()){
        const Token * next;
        view >> next;
        Util::CReferenceCount<CSequence> sequence = parseSequence(next, images, baseDir);
        if (sequence != NULL){
            addSequence(sequence);
        }
    }
}

int CSequenceLoop::totalTicks() const {
    int total = 0;
    for (vector<Util::CReferenceCount<CSequence> >::const_iterator it = frames.begin(); it != frames.end(); it++){
        const Util::CReferenceCount<CSequence> & sequence = *it;
        total += sequence->totalTicks();
    }
    return total * (1 + loopTimes);
}

bool CSequenceLoop::forward(int tickCount, double velocityX, double velocityY){
    Util::CReferenceCount<CSequence> current = getCurrentSequence();
    if (current != NULL){
        if (current->forward(tickCount, velocityX, velocityY)){
            forwardFrame();
        }
    }

    return currentFrame == frames.size();
}

bool CSequenceLoop::reverse(int tickCount, double velocityX, double velocityY){
    Util::CReferenceCount<CSequence> current = getCurrentSequence();
    if (current != NULL){
        if (current->reverse(tickCount, velocityX, velocityY)){
            backFrame();
        }
    }

    return currentFrame == frames.size();
}

void CSequenceLoop::forwardFrame(){
    currentFrame += 1;

    /* do the loop */
    if (currentFrame == frames.size() && currentLoop > 0){
        currentLoop -= 1;
        currentFrame = 0;
        resetChildrenTicks();
    }
}

void CSequenceLoop::backFrame(){
    currentFrame -= 1;

    /* do the loop */
    if (currentFrame <= 0 && currentLoop > 0){
        currentLoop -= 1;
        resetChildrenTicks();
        if (frames.size() > 0){
            currentFrame = frames.size() - 1;
        } else {
            currentFrame = 0;
        }
    }
}

CSequenceAll::CSequenceAll(const Token * token, ImageMap & images, const string & baseDir){
    TokenView view = token->view();
    while (view.hasMore()){
        const Token * next;
        view >> next;
        Util::CReferenceCount<CSequence> sequence = parseSequence(next, images, baseDir);
        if (sequence != NULL){
            addSequence(sequence);
        }
    }
}

Util::CReferenceCount<CElement> CSequenceAll::getCurrentFrame() const {
    return Util::CReferenceCount<CElement>(NULL);
}

void CSequenceAll::reset(){
    for (SequenceIterator it = sequences.begin(); it != sequences.end(); it++){
        Util::CReferenceCount<CSequence> & next = *it;
        next->reset();
    }
}

void CSequenceAll::resetTicks(){
    for (SequenceIterator it = sequences.begin(); it != sequences.end(); it++){
        Util::CReferenceCount<CSequence> & next = *it;
        next->resetTicks();
    }
}

void CSequenceAll::setToEnd(){
    for (SequenceIterator it = sequences.begin(); it != sequences.end(); it++){
        Util::CReferenceCount<CSequence> & next = *it;
        next->setToEnd();
    }
}

void CSequenceAll::addSequence(const Util::CReferenceCount<CSequence> & sequence){
    sequences.push_back(sequence);
}

void CSequenceAll::draw(int xaxis, int yaxis, const CBitmap & work){
    for (SequenceIterator it = sequences.begin(); it != sequences.end(); it++){
        Util::CReferenceCount<CSequence> & next = *it;
        next->draw(xaxis, yaxis, work);
    }
}

/* Maximum ticks of any sequence */
int CSequenceAll::totalTicks() const {
    int max = 0;
    for (SequenceConstIterator it = sequences.begin(); it != sequences.end(); it++){
        const Util::CReferenceCount<CSequence> & next = *it;
        int what = next->totalTicks();
        if (what > max){
            max = what;
        }
    }
    return max;
}

bool CSequenceAll::forward(int tickCount, double velocityX, double velocityY){
    bool go = false;
    for (SequenceIterator it = sequences.begin(); it != sequences.end(); it++){
        Util::CReferenceCount<CSequence> & next = *it;
        go = next->forward(tickCount, velocityX, velocityY) && go;
    }
    return go;
}

bool CSequenceAll::reverse(int tickCount, double velocityX, double velocityY){
    bool go = false;
    for (SequenceIterator it = sequences.begin(); it != sequences.end(); it++){
        Util::CReferenceCount<CSequence> & next = *it;
        go = next->reverse(tickCount, velocityX, velocityY) && go;
    }
    return go;
}

void CSequenceAll::forwardFrame(){
    for (SequenceIterator it = sequences.begin(); it != sequences.end(); it++){
        Util::CReferenceCount<CSequence> & next = *it;
        next->forwardFrame();
    }
}

void CSequenceAll::backFrame(){
    for (SequenceIterator it = sequences.begin(); it != sequences.end(); it++){
        Util::CReferenceCount<CSequence> & next = *it;
        next->backFrame();
    }
}

CSequenceRandom::CSequenceRandom(const Token * token, ImageMap & images, const string & baseDir):
current(0){
    TokenView view = token->view();
    while (view.hasMore()){
        const Token * next;
        view >> next;
        Util::CReferenceCount<CSequence> sequence = parseSequence(next, images, baseDir);
        if (sequence != NULL){
            addSequence(sequence);
        }
    }

    current = Util::rnd(sequences.size());
}

Util::CReferenceCount<CElement> CSequenceRandom::getCurrentFrame() const {
    return Util::CReferenceCount<CElement>(NULL);
}

void CSequenceRandom::reset(){
    current = Util::rnd(sequences.size());
    for (SequenceIterator it = sequences.begin(); it != sequences.end(); it++){
        Util::CReferenceCount<CSequence> & next = *it;
        next->reset();
    }
}

void CSequenceRandom::resetTicks(){
    current = Util::rnd(sequences.size());
    for (SequenceIterator it = sequences.begin(); it != sequences.end(); it++){
        Util::CReferenceCount<CSequence> & next = *it;
        next->resetTicks();
    }
}

void CSequenceRandom::setToEnd(){
    for (SequenceIterator it = sequences.begin(); it != sequences.end(); it++){
        Util::CReferenceCount<CSequence> & next = *it;
        next->setToEnd();
    }
}

void CSequenceRandom::addSequence(const Util::CReferenceCount<CSequence> & sequence){
    sequences.push_back(sequence);
}

void CSequenceRandom::draw(int xaxis, int yaxis, const CBitmap & work){
    if (current < sequences.size()){
        Util::CReferenceCount<CSequence> now = sequences[current];
        now->draw(xaxis, yaxis, work);
    }
}

int CSequenceRandom::totalTicks() const {
    int max = 0;
    for (SequenceConstIterator it = sequences.begin(); it != sequences.end(); it++){
        const Util::CReferenceCount<CSequence> & next = *it;
        int what = next->totalTicks();
        if (what > max){
            max = what;
        }
    }
    return max;
}

bool CSequenceRandom::forward(int tickCount, double velocityX, double velocityY){
    if (current < sequences.size()){
        Util::CReferenceCount<CSequence> now = sequences[current];
        return now->forward(tickCount, velocityX, velocityY);
    }
    return true;
}

bool CSequenceRandom::reverse(int tickCount, double velocityX, double velocityY){
    if (current < sequences.size()){
        Util::CReferenceCount<CSequence> now = sequences[current];
        return now->reverse(tickCount, velocityX, velocityY);
    }
    return true;
}

void CSequenceRandom::forwardFrame(){
    if (current < sequences.size()){
        sequences[current]->forwardFrame();
    }
}

void CSequenceRandom::backFrame(){
    if (current < sequences.size()){
        sequences[current]->backFrame();
    }
}

static int CURRENT_ID = 0;

static int getNextId(){
    return CURRENT_ID++;
}

CAnimation::CAnimation(const Token *the_token):
id(getNextId()),
depth(BackgroundBottom),
allowReset(true),
sequence(0){
    /* Whats this for? */
    images[-1] = 0;
    string basedir = ".";
	   Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN LOAD ANIMATION:" << endl;
	   the_token->print(" ");

    if ( *the_token != "anim" && *the_token != "animation" ){
        throw CLoadException(__FILE__, __LINE__, "Not an animation");
    }
    /* The usual setup of an animation is
	The images must be listed prior to listing any frames, basedir can be used to set the directory where the images are located
	loop will begin at the subsequent frame listed after loop
	axis is the location in which the drawing must be placed
	location *old* - used to render in background or foreground (0 == background [default]| 1 == foreground)
    depth - used to render in background or foreground space (depth background bottom|middle|top) | (depth foreground bottom|midle|top)
	reset - used to allow resetting of animation (0 == no | 1 == yes [default])
	velocity - used to get a wrapping scroll effect while animating
    window - area in which the item will be contained
	(anim (id NUM)
	      (location NUM)
              (scale NUM) ;; optional
              (depth background|foreground NUM)
	      (basedir LOCATION)
	      (image NUM FILE [SCALE])
	      (velocity x y)
	      (axis x y)
	      (frame "Read comments above in constructor")
	      (loop 2)
	      (reset NUM)
	      (window x1 y1 x2 y2))
    */
    double scale = 1.0;
    bool scaleSet = false;
    const Token & tok = *the_token;
    TokenView view = tok.view();
    while (view.hasMore()){
        try{
            const Token * token;
            view >> token;
            if (*token == "id"){
                // get the id
                token->view() >> id;
            } else if (*token == "location"){
                // translate location to depth
                /*int location = 0;
                token->view() >> location;
                if (location == 0){
                    depth = BackgroundBottom;
                } else if (location == 1){
                    depth = ForegroundBottom;
                }*/
                Debug::debug(Debug::error,__FUNCTION__) << "The option (" << token->getLineage() << ") in the file '" << token->getFileName() << "' is no longer valid and will be ignored. Consider using 'depth' instead." << endl;
            } else if (*token == "scale"){
                token->view() >> scale;
                scaleSet = true;
            } else if (*token == "depth"){
                // get the depth
                string name, level;
                token->view() >> name >> level;
                if (name == "background"){
                    if (level == "bottom"){
                        depth = BackgroundBottom;
                    } else if (level == "middle"){
                        depth = BackgroundMiddle;
                    } else if (level == "top"){
                        depth = BackgroundTop;
                    }
                } else if (name == "foreground"){
                    if (level == "bottom"){
                        depth = ForegroundBottom;
                    } else if (level == "middle"){
                        depth = ForegroundMiddle;
                    } else if (level == "top"){
                        depth = ForegroundTop;
                    }
                }
            } else if (*token == "basedir"){
                // set the base directory for loading images
                token->view() >> basedir;
            } else if (*token == "image"){
                // add bitmaps by number to the map
                int number;
                string temp;
                double localScale = 1;
                bool localScaleSet = false;
                TokenView view = token->view();
                view >> number >> temp;
                try{
                    view >> localScale;
                    localScaleSet = true;
                } catch (const CTokenException & fail){
                }

                Util::CReferenceCount<CBitmap> bmp(new CBitmap(Filesystem::getInstance().find(Filesystem::CRelativePath(basedir + "/" + temp)).path()));
               
				if (!bmp->getError()){
                    if (scaleSet || localScaleSet){
                        if (localScaleSet){
                      //s      *bmp = bmp->scaleBy(localScale, localScale);
                        } else {
                        //s    *bmp = bmp->scaleBy(scale, scale);
                        }
                    }
                    images[number] = bmp;
                }
            } else if (*token == "axis"){
                // Get the axis location it defaults to 0,0
                double x=0, y=0;
                try {
                    token->view() >> x >> y;
                } catch (const CTokenException & ex){
                }
                axis.set(x,y);
            } else if (*token == "window"){
                // Windowed area where to clip if necessary otherwise it defaults to max
                double x1=0,x2=0, y1=0,y2=0;
                try {
                    token->view() >> x1 >> y1 >> x2 >> y2;
                } catch (const CTokenException & ex){
                }
                window.set(x1,y1,x2,y2);
            } else if (*token == "velocity"){
                // This allows the animation to get a wrapping scroll action going on
                double x=0, y=0;
                try {
                    token->view() >> x >> y;
                } catch (const CTokenException & ex){
                }
                velocity.set(x,y);
            } else if (*token == "frame"){
                Util::CReferenceCount<CElement> frame(new CImageFrame(token, images, basedir));
                sequence.addSequence(Util::CReferenceCount<CSequence>(new CSequenceFrame(frame)));
            } else if (*token == "text"){
                Util::CReferenceCount<CElement> frame(new CTextFrame(token));
                sequence.addSequence(Util::CReferenceCount<CSequence>(new CSequenceFrame(frame)));
            } else if (*token == "all"){
                sequence.addSequence(Util::CReferenceCount<CSequence>(new CSequenceAll(token, images, basedir)));
            } else if (*token == "random"){
                sequence.addSequence(Util::CReferenceCount<CSequence>(new CSequenceRandom(token, images, basedir)));
            } else if (*token == "loop"){
                // start loop here
                int times;
                token->view() >> times;
                Util::CReferenceCount<CSequenceLoop> loop(new CSequenceLoop(times));
                loop->parse(token, images, basedir);
                sequence.addSequence(loop);

                /*
		if (l >= (int)frames.size()){
		    ostringstream out;
		    out << "Loop location is larger than the number of frames. Loop: " << loop << " Frames: " << frames.size();
		    throw CLoadException(__FILE__, __LINE__, out.str());
		}
                */
            } else if (*token == "reset"){
                // Allow reset of animation
                token->view() >> allowReset;
            } else {
                Debug::debug(Debug::menu,__FUNCTION__) << "Unhandled menu attribute: "<<endl;
             //   if (Global::getDebug() >= 3){
             //       token->print(" ");
             //   }
            }
        } catch ( const CTokenException & ex ) {
            throw CLoadException(__FILE__, __LINE__, ex, "Menu animation parse error");
        } catch ( const CLoadException & ex ) {
            throw ex;
        }
    }
}

CAnimation::CAnimation(const string & background):
id(getNextId()),
depth(BackgroundBottom),
allowReset(true),
sequence(0){
    // add bitmap
	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN - WILL CREATE BITMAP" << endl;
    Util::CReferenceCount<CBitmap> bmp(new CBitmap(Filesystem::getInstance().find(Filesystem::CRelativePath(background)).path()));
    if (bmp->getError()){
        throw CLoadException(__FILE__,__LINE__, "Problem loading file: " + background);
    } else {
        images[0] = bmp;
    }
	Debug::debug(Debug::gui,__FUNCTION__) << "END CREATE BITMAP" << endl;

	Debug::debug(Debug::gui,__FUNCTION__) << "WILL CREATE FRAME" << endl;

    Util::CReferenceCount<CElement> frame(new CImageFrame(bmp));
   Debug::debug(Debug::gui,__FUNCTION__) << "END CREATE FRAME" << endl;
	sequence.addSequence(Util::CReferenceCount<CSequence>(new CSequenceFrame(frame)));
    Debug::debug(Debug::gui,__FUNCTION__) << "END " << endl;
}

CAnimation::CAnimation(const Filesystem::CAbsolutePath & path):
id(getNextId()),
depth(BackgroundBottom),
allowReset(true),
sequence(0){
    // add bitmap
    Util::CReferenceCount<CBitmap> bmp(new CBitmap(path.path()));
    if (bmp->getError()){
        throw CLoadException(__FILE__,__LINE__, "Problem loading file: " + path.path());
    } else {
        images[0] = bmp;
    }
    Util::CReferenceCount<CElement> frame(new CImageFrame(bmp));
    sequence.addSequence(Util::CReferenceCount<CSequence>(new CSequenceFrame(frame)));
}

CAnimation::CAnimation(Util::CReferenceCount<CBitmap> image):
id(getNextId()),
depth(BackgroundBottom),
allowReset(true),
sequence(0){
    images[0] = image;
    Util::CReferenceCount<CElement> frame(new CImageFrame(image));
    sequence.addSequence(Util::CReferenceCount<CSequence>(new CSequenceFrame(frame)));
}

CAnimation::~CAnimation(){
}

int CAnimation::totalTicks() const {
    return sequence.totalTicks();
}

void CAnimation::forward(int tickCount){
    sequence.forward(tickCount, velocity.getRelativeX(), velocity.getRelativeY());
}

void CAnimation::reverse(int tickCount){
    sequence.reverse(tickCount, velocity.getRelativeX(), velocity.getRelativeY());
}

void CAnimation::act(){
    forward();
}

void CAnimation::draw(const CBitmap & work){
    /* FIXME: should use sub-bitmaps here */
    /*const int x = window.getX();
    const int y = window.getY();
    const int width = window.getWidth();
    const int height = window.getHeight();
    Debug::debug(Debug::error,__FUNCTION__) << "Distance x2: " << width << " Distance y2: " << height << endl;
    CBitmap clipped(work, x, y, height, width);
    frames[currentFrame]->draw(0, 0,clipped);*/
     // Set clip from the axis default is 0,0,bitmap width, bitmap height
/*    work.setClipRect(-window.getPosition().getDistanceFromCenterX(),
                     -window.getPosition().getDistanceFromCenterY(),
                     work.getWidth() - window.getPosition2().getDistanceFromCenterX(),
                     work.getHeight() - window.getPosition2().getDistanceFromCenterY());
					 */
	work.setClipRect(-(window.getPosition().getDistanceFromCenterX()),-(window.getPosition().getDistanceFromCenterY()),work.getWidth() - window.getPosition2().getDistanceFromCenterX(),work.getHeight() - window.getPosition2().getDistanceFromCenterY());

    sequence.draw(axis.getDistanceFromCenterX(), axis.getDistanceFromCenterY(), work);
	work.setClipRect(0,0,work.getWidth(),work.getHeight());

}

void CAnimation::draw(int x, int y, int width, int height, const CBitmap & work){
    const Util::CReferenceCount<CElement> & frame = sequence.getCurrentFrame();
    if (frame != NULL){
        CBitmap clipped(work, x, y, width, height);
        frame->draw(clipped);
    }
}

void CAnimation::forwardFrame(){
    sequence.forwardFrame();
}

void CAnimation::backFrame(){
    sequence.backFrame();
}

void CAnimation::reset(){
    sequence.reset();
}

void CAnimation::resetAll(){
    sequence.reset();
}

void CAnimation::setToEnd(){
    /* FIXME */
    sequence.setToEnd();
    // currentFrame = frames.size()-1;
    // currentLoop = 0;
    // Set offsets
    /*
    for (vector<Util::CReferenceCount<CElement> >::iterator i = frames.begin(); i != frames.end(); ++i){
        Util::CReferenceCount<CElement> frame = *i;
        frame->setToEnd(CRelativePoint(ticks * velocity.getRelativeX(), ticks * velocity.getRelativeY()));
    }
    */
}

const string CAnimation::getInfo(){
    /*
    static const char * ANIMATION_TEXT = "CAnimation ID: %d\nTicks: %d\nFrame Index: %d\nLoop From: %d\nAxis: ( %f, %f)\nVelocity: ( %f, %f)\n";
    char info[255];
    sprintf(info, ANIMATION_TEXT, id, ticks, currentFrame, loop, axis.getRelativeX(), axis.getRelativeY(), velocity.getRelativeX(), velocity.getRelativeY());
    return string(info) + frames[currentFrame]->getInfo();
    */
    /* FIXME */
    ostringstream out;
    out << "CAnimation ID: " << id;
    return out.str();
}

CAnimationManager::CAnimationManager(){
    // Set the current id to 0 for each context
    CURRENT_ID = 0;
}

CAnimationManager::CAnimationManager(const CAnimationManager & copy):
animations(copy.animations){
    // Set the current id to 0 for each context
    CURRENT_ID = 0;
}

CAnimationManager::~CAnimationManager(){
}

const CAnimationManager & CAnimationManager::operator=(const CAnimationManager & copy){
    animations = copy.animations;
    return *this;
}


void CAnimationManager::forward(int tickCount){
    for (map<Gui::CAnimation::Depth, vector<Util::CReferenceCount<Gui::CAnimation> > >::iterator i = animations.begin(); i != animations.end(); ++i){
        vector<Util::CReferenceCount<Gui::CAnimation> > & animations = i->second;
        for (vector<Util::CReferenceCount<Gui::CAnimation> >::iterator j = animations.begin(); j != animations.end(); ++j){
            Util::CReferenceCount<Gui::CAnimation> animation = *j;
            if (animation != NULL){
                animation->forward(tickCount);
            }
        }
    }
}

void CAnimationManager::reverse(int tickCount){
    for (map<Gui::CAnimation::Depth, vector<Util::CReferenceCount<Gui::CAnimation> > >::iterator i = animations.begin(); i != animations.end(); ++i){
        vector<Util::CReferenceCount<Gui::CAnimation> > & animations = i->second;
        for (vector<Util::CReferenceCount<Gui::CAnimation> >::iterator j = animations.begin(); j != animations.end(); ++j){
            Util::CReferenceCount<Gui::CAnimation> animation = *j;
            if (animation != NULL){
                animation->reverse(tickCount);
            }
        }
    }
}

void CAnimationManager::act(){
    forward();
}

void CAnimationManager::render(const Gui::CAnimation::Depth & depth, const CBitmap & work){
    for (vector<Util::CReferenceCount<Gui::CAnimation> >::iterator i = animations[depth].begin(); i != animations[depth].end(); ++i){
        Util::CReferenceCount<Gui::CAnimation> animation = *i;
        if (animation != NULL){
            animation->draw(work);
        }
    }
}

void CAnimationManager::add(Util::CReferenceCount<Gui::CAnimation > animation){
   Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN - Adding New Animation TO Animation Manager" << endl;
	animations[animation->getDepth()].push_back(animation);

}

void CAnimationManager::reset(){
    for (map<Gui::CAnimation::Depth, vector<Util::CReferenceCount<Gui::CAnimation> > >::iterator i = animations.begin(); i != animations.end(); ++i){
        vector<Util::CReferenceCount<Gui::CAnimation> > & animations = i->second;
        for (vector<Util::CReferenceCount<Gui::CAnimation> >::iterator j = animations.begin(); j != animations.end(); ++j){
            Util::CReferenceCount<Gui::CAnimation> animation = *j;
            if (animation != NULL){
                animation->resetAll();
            }
        }
    }
}

int CAnimationManager::totalTicks() const {
    int count = 0;
    for (map<Gui::CAnimation::Depth, vector<Util::CReferenceCount<Gui::CAnimation> > >::const_iterator it = animations.begin(); it != animations.end(); it++){
        //Gui::CAnimation::Depth depth = it->first;
        const vector<Util::CReferenceCount<Gui::CAnimation> > & stuff = it->second;
        int next = countTicks(stuff);
        /* If any animation takes infinite time then the whole thing takes infinite time */
        if (next == -1){
            return -1;
        }
        if (next > count){
            count = next;
        }
    }
    return count;
}

int CAnimationManager::countTicks(const vector<Util::CReferenceCount<CAnimation> > & toCount) const {
    int total = 0;
    for (vector<Util::CReferenceCount<CAnimation> >::const_iterator it = toCount.begin(); it != toCount.end(); it++){
        const Util::CReferenceCount<CAnimation> & animation = *it;
        int ticks = animation->totalTicks();
        if (ticks == -1){
            return ticks;
        }
        total += ticks;
    }
    return total;
}

void CAnimationManager::setToEnd(){
    for (map<Gui::CAnimation::Depth, vector<Util::CReferenceCount<Gui::CAnimation> > >::iterator i = animations.begin(); i != animations.end(); ++i){
        vector<Util::CReferenceCount<Gui::CAnimation> > & animations = i->second;
        for (vector<Util::CReferenceCount<Gui::CAnimation> >::iterator j = animations.begin(); j != animations.end(); ++j){
            Util::CReferenceCount<Gui::CAnimation> animation = *j;
            if (animation != NULL){
                animation->setToEnd();
            }
        }
    }
}

const string CAnimationManager::getInfo(int id, bool all){
    string info("");
    for (map<Gui::CAnimation::Depth, vector<Util::CReferenceCount<Gui::CAnimation> > >::iterator i = animations.begin(); i != animations.end(); ++i){
        vector<Util::CReferenceCount<Gui::CAnimation> > & animations = i->second;
        for (vector<Util::CReferenceCount<Gui::CAnimation> >::iterator j = animations.begin(); j != animations.end(); ++j){
            Util::CReferenceCount<Gui::CAnimation> animation = *j;
            if (animation != NULL){
                if (id == animation->getID() || all){
                    info += animation->getInfo();
                }
            }
        }
    }
    return info;
}

const vector<int> CAnimationManager::getIdList(){
    vector<int> list;
    for (map<Gui::CAnimation::Depth, vector<Util::CReferenceCount<Gui::CAnimation> > >::iterator i = animations.begin(); i != animations.end(); ++i){
        vector<Util::CReferenceCount<Gui::CAnimation> > & animations = i->second;
        for (vector<Util::CReferenceCount<Gui::CAnimation> >::iterator j = animations.begin(); j != animations.end(); ++j){
            Util::CReferenceCount<Gui::CAnimation> animation = *j;
            if (animation != NULL){
                list.push_back(animation->getID());
            }
        }
    }
    return list;
}
} //end SGF