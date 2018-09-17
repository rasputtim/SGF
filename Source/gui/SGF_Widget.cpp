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


#include "gui/SGF_Widget.h"
#include "util/SGF_Util.h"
#include <math.h>
#include <sstream>
#include "graphics/SGF_Poligon.h"

using namespace std;
namespace SGF{

using namespace Gui;

static const double S_PI = 3.14159265358979323846;
static const double DEG_TO_RAD = 180.0/S_PI;
static const double RAD_TO_DEG = S_PI/180.0;

static void round_double (double dbl_to_round , int &rounded_num) {
		rounded_num = static_cast<int>(dbl_to_round);
		if ((dbl_to_round - static_cast<double>(rounded_num)) >= 0.5) {rounded_num++;}
	}

//! min (borrowed from allegro)
static inline int Min(int x, int y){ return (((x) < (y)) ? (x) : (y)); }

//! max (borrowed from allegro)
static inline int Max(int x, int y){ return (((x) > (y)) ? (x) : (y)); }

//! mid (borrowed from allegro)
static inline int Mid(int x,int y,int z){ return (Max((x), Min((y), (z)))); }

static Uint8 clamp(Uint8 in, Uint8 low = 0, Uint8 high = 255){
    return Util::clamp(in,low,high);
}

CTransformations::CTransformations():
radius(0){
}

CTransformations::CTransformations(const CTransformations & transforms):
radius(transforms.radius){
}

CTransformations::~CTransformations(){
}

CTransformations & CTransformations::operator=(const CTransformations & transforms){
    this->radius = transforms.radius;
    return *this;
}



CWidget::CWidget() : position(0,0,0,0), workArea(0)
{
	// Nothing yet
}

CWidget::CWidget( const CWidget & w ){
	this->location = w.location;
	this->position = w.position;
	this->workArea = w.workArea;
}

CWidget::~CWidget(){
	if ( workArea ){
		delete workArea;
	}
}

// copy
CWidget &CWidget::operator=( const CWidget &copy){
	location = copy.location;
	position = copy.position;
	workArea = copy.workArea;

	return *this;
}
/*
void CWidget::arc( CBitmap *work, int x, int y, double startAngle, int radius,  Colors::ColorDefinition color )
{
	Uint32 pixel = Colors::makeColor(color.r,color.g,color.b);
	arc(work,x,y,startAngle,radius,pixel);
}
void CWidget::arc( CBitmap *work, int x, int y, double startAngle, int radius, Uint32 pixel )
{
	int q = 0;// for counters
	double d_q = 0.0;// for percentage of loop completed
	double d_q_plus_one = 0.0;

	const double d_angular_length_deg = 0.030;
	const double d_start_angle_rad = startAngle*DEG_TO_RAD;
	const double d_angular_length_rad = d_angular_length_deg*DEG_TO_RAD;
	const double d_arc_distance_between_points = 0.25*pow(2.0 , static_cast<double>(10) / 10.0);
	double d_angular_length_rad_per_segment = 0.0;

	double arc_length = radius*d_angular_length_rad;
	if (arc_length < 0.0) {arc_length *= -1.0;}
	const double d_num_segments = arc_length / d_arc_distance_between_points;

	int num_segments = 0;
	round_double(d_num_segments , num_segments);

	if (num_segments == 0) {num_segments += 1;} // need at least one segment (two points)
	const int num_points = num_segments + 1;
	const double d_num_points_minus_one = static_cast<double>(num_points - 1);

	int arc_point_x;//[num_points];
	int arc_point_y;//[num_points];
	int arc_point2_x;//[num_points];
	int arc_point2_y;//[num_points];
	double d_arc_point_x = 0.0;
	double d_arc_point_y = 0.0;
	double d_arc_point2_x = 0.0;
	double d_arc_point2_y = 0.0;

	double current_angle_rad = 0.0;
	double current_angle2_rad = 0.0;

	if (d_arc_distance_between_points <= 1.0) {
		for (q = 0 ; q < num_points ; q++) {
			d_q = static_cast<double>(q);
			current_angle_rad = d_start_angle_rad + (d_q / d_num_points_minus_one)*d_angular_length_rad;
			d_arc_point_x = x + radius*cos(current_angle_rad);
			d_arc_point_y = y + radius*sin(current_angle_rad);

			round_double(d_arc_point_x , arc_point_x);
			round_double(d_arc_point_y , arc_point_y);

			////todo corrigir putpixel
			work->putPixelSurface(arc_point_x,arc_point_y,pixel);
		}
	}
	if (d_arc_distance_between_points > 1.0) {

		d_angular_length_rad_per_segment = d_angular_length_rad / d_num_points_minus_one;
		for (q = 0 ; q < num_segments ; q++) {
			d_q = static_cast<double>(q);
			d_q_plus_one = static_cast<double>(q + 1);

			current_angle_rad = d_start_angle_rad + d_q*d_angular_length_rad_per_segment;
			current_angle2_rad = d_start_angle_rad + d_q_plus_one*d_angular_length_rad_per_segment;

			d_arc_point_x = x + radius*cos(current_angle_rad);
			d_arc_point_y = y + radius*sin(current_angle_rad);

			round_double(d_arc_point_x , arc_point_x);
			round_double(d_arc_point_y , arc_point_y);

			d_arc_point2_x = x + radius*cos(current_angle2_rad);
			d_arc_point2_y = y + radius*sin(current_angle2_rad);

			round_double(d_arc_point2_x , arc_point2_x);
			round_double(d_arc_point2_y , arc_point2_y);

			work->line(arc_point_x,arc_point_y, arc_point2_x, arc_point2_y,pixel);
		}
	}
}*/
void CWidget::roundRect( CBitmap *work, int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color )
{
   Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN" <<  endl;
// Uint32 pixel = Colors::makeColor(color.r,color.g,color.b);
	const int width = x2 - x1;
	const int height = y2 - y1;
	radius = Mid(0, radius, Min((x1+width - x1)/2, (y1+height - y1)/2));
	work->polygon().line(x1+radius, y1, x1+width-radius, y1, color);
	work->polygon().line(x1+radius, y1+height, x1+width-radius,y1+height, color);
	work->polygon().line(x1, y1+radius,x1, y1+height-radius, color);
	work->polygon().line(x1+width, y1+radius,x1+width, y1+height-radius, color);
	work->polygon().arc(x1+radius, y1+radius,180,270,radius,color);
	work->polygon().arc((x1+width)-radius, y1+radius,270,360,radius,color);
	work->polygon().arc(x1+radius, (y1+height)-radius,90,180,radius,color);
	work->polygon().arc((x1+width)-radius, (y1+height)-radius,0,90,radius,color);
	//roundRect(work,radius,x1,y1,x2,y2,pixel);
	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN" <<  endl;

}
/*
void CWidget::roundRect( CBitmap *work, int radius, int x1, int y1, int x2, int y2, Uint32 pixel )
{

	const int width = x2 - x1;
	const int height = y2 - y1;
	radius = Mid(0, radius, Min((x1+width - x1)/2, (y1+height - y1)/2));
	work->line(x1+radius, y1, x1+width-radius, y1, pixel);
	work->line(x1+radius, y1+height, x1+width-radius,y1+height, pixel);
	work->line(x1, y1+radius,x1, y1+height-radius, pixel);
	work->line(x1+width, y1+radius,x1+width, y1+height-radius, pixel);
	work->arc(x1+radius, y1+radius,180,270,radius,pixel);
	work->arc((x1+width)-radius, y1+radius,270,360,radius,pixel);
	work->arc(x1+radius, (y1+height)-radius,90,180,radius,pixel);
	work->arc((x1+width)-radius, (y1+height)-radius,0,90,radius,pixel);

} */
void CWidget::roundRectFill( CBitmap *work, int radius, int x1, int y1, int x2, int y2,  Colors::ColorDefinition color )
{
    //Uint32 cor = Colors::makeColor(color.r,color.g,color.b);
	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN" <<  endl;

	const int width = x2 - x1;
	const int height = y2 - y1;
	radius = Mid(0, radius, Min((x1+width - x1)/2, (y1+height - y1)/2));
	work->polygon().pieFill(x1+radius, y1+radius,180,275,radius,color);
	work->polygon().pieFill((x1+width)-radius, y1+radius,270,362,radius,color);
	work->polygon().pieFill(x1+radius, (y1+height)-radius,90,183,radius,color);
	work->polygon().pieFill((x1+width)-radius, (y1+height)-radius,0,93,radius,color);
	work->polygon().rectangleFill( x1+radius, y1, x2-radius, y1+radius, color);
	work->polygon().rectangleFill( x1, y1+radius, x2, y2-radius, color);
	work->polygon().rectangleFill( x1+radius, y2-radius, x2-radius, y2, color);

	Debug::debug(Debug::gui,__FUNCTION__) << "END" <<  endl;

	//roundRectFill(work,radius,x1,y1,x2,y2,cor);
}

/*
void CWidget::roundRectFill( CBitmap *work, int radius, int x1, int y1, int x2, int y2, Uint32 pixel)
{
	const int width = x2 - x1;
	const int height = y2 - y1;
	radius = Mid(0, radius, Min((x1+width - x1)/2, (y1+height - y1)/2));
	work->pieFill(x1+radius, y1+radius,180,275,radius,pixel);
	work->pieFill((x1+width)-radius, y1+radius,270,362,radius,pixel);
	work->pieFill(x1+radius, (y1+height)-radius,90,183,radius,pixel);
	work->pieFill((x1+width)-radius, (y1+height)-radius,0,93,radius,pixel);
	work->rectangleFill( x1+radius, y1, x2-radius, y1+radius, pixel);
	work->rectangleFill( x1, y1+radius, x2, y2-radius, pixel);
	work->rectangleFill( x1+radius, y2-radius, x2-radius, y2, pixel);
}
*/
void CWidget::checkWorkArea()
{
	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN" <<  endl;
	if ( ! workArea ){
		workArea = new CBitmap(position.width,position.height);
	} else if(position.width < workArea->getWidth() || position.height < workArea->getHeight()) {
		delete workArea;
		workArea = new CBitmap(position.width,position.height);
	} else if(position.width > workArea->getWidth() || position.height > workArea->getHeight()) {
		delete workArea;
		workArea = new CBitmap(position.width,position.height);
	}
	if ( workArea ){
		workArea->setBitmapMode(CBitmap::DRAW_TYPE_SURFACE);
		workArea->fill(255,0,255);  //preenche com magenta
		workArea->setBitmapMode(CBitmap::DRAW_TYPE_DEFAULT);
	}
	Debug::debug(Debug::gui,__FUNCTION__) << "END" <<  endl;
}

Util::CReferenceCount<CBitmap> CWidget::checkWorkArea(const CBitmap & parent){
    if (location.getWidth() <= 0 || location.getHeight() <= 0){
        return Util::CReferenceCount<CBitmap>(NULL);
    }
	if (&parent==NULL) {
		Util::CReferenceCount<CBitmap> tempBitmap=Util::CReferenceCount<CBitmap>(new CBitmap(location.getWidth(), location.getHeight()));
		tempBitmap->useSurface();
		tempBitmap->fill(255,0,255);
		tempBitmap->applyDefTrans();  //update texture
		tempBitmap->SetBlendMode(CBitmap::MODE_TRANS);
		return tempBitmap;
	}else {
	    return Util::CReferenceCount<CBitmap>(new CBitmap(parent, location.getX(), location.getY(), location.getWidth(), location.getHeight()));
	}
}
void CWidget::setCoordinates(const Token * token) throw(CLoadException){
	Debug::debug(Debug::gui,__FUNCTION__) << "BEGIN / Setting Widget Positions: " << token->getName() << endl;
    if ( *token == "position" ){
        int x, y, width, height;
        token->view() >> x >> y >> width >> height;
		Debug::debug(Debug::gui,__FUNCTION__) << "position/dimention [x1,y1,x2(x+w),y2(y+h)] [" << x<<" , "<<y<<" , "<<x + width <<" , "<<y + height<<" ]"<< endl;
        CAbsolutePoint pos(x, y);
        CAbsolutePoint dimensions(x + width, y + height);
        location.setPosition(pos);
        location.setPosition2(dimensions);
    } else if ( *token == "relative-position" ){
        double x1, y1, x2, y2;
        token->view() >> x1 >> y1 >> x2 >> y2;
        CRelativePoint pos(x1,y1);
        CRelativePoint dimensions(x2,y2);
        location = CCoordinate(pos, dimensions);
    } else if ( *token == "coordinate" ){
        TokenView view = token->view();
        while (view.hasMore()){
            const Token * coordToken;
            view >> coordToken;
            if (*coordToken == "absolute"){
                int x, y, width, height;
                coordToken->view() >> x >> y >> width >> height;
                CAbsolutePoint pos(x, y);
                CAbsolutePoint dimensions(x + width, y + height);
                location = CCoordinate(pos, dimensions);
            } else if (*coordToken == "relative"){
                double x1, y1, x2, y2;
                coordToken->view() >> x1 >> y1 >> x2 >> y2;
                CRelativePoint pos(x1,y1);
                CRelativePoint dimensions(x2,y2);
                location = CCoordinate(pos, dimensions);
            } else if (*coordToken == "radius"){
                double radius;
                coordToken->view() >> radius;
                location.setRadius(radius);
            } else if (*coordToken == "z"){
                double z;
                coordToken->view() >> z;
                location.setZ(z);
            }
        }
    }

    if (location.getWidth() < 0 || location.getHeight() < 0){
        ::std::ostringstream out;
        out << "Invalid location dimension (cannot have a negative size). Width " << location.getWidth() << " Height " << location.getHeight() << ". From token: ";
        //token->toString(out, "");
        throw CLoadException(__FILE__, __LINE__, out.str());
    }
	Debug::debug(Debug::menu,__FUNCTION__) << "END" << endl;
}

void CWidget::setColors(const Token * token){
    if ( *token == "position-body" ) {
        // This handles the body color of the widget
        int r,g,b,a;
        token->view() >> r >> g >> b >>a;
        Colors::ColorDefinition tempColor={ clamp(r),clamp(g),clamp(b),clamp(a)};
		colors.body = tempColor;
    } else if ( *token == "position-border" ) {
        // This handles the border color of the widget
        int r,g,b,a;
        token->view() >> r >> g >> b >> a;
		Colors::ColorDefinition tempColor={ clamp(r),clamp(g),clamp(b),clamp(a)};
		colors.border = tempColor;
    }
}
void CWidget::setTransforms(const Token * token){
    try{
        if ( *token != "transforms" ){
            throw CLoadException(__FILE__, __LINE__, "Not a Widget Transforms.");
        }
        TokenView view = token->view();
        while (view.hasMore()){
            const Token * tok;
            view >> tok;
            double radius = 0;
            try{
                if (tok->match("radius", radius)){
                    transforms.setRadius(radius);
                } else {
					Debug::debug(Debug::gui,__FUNCTION__) << "Unknown Transforms property: " << tok->getName() << endl;
                }
            } catch (const CTokenException & ex){
                throw CLoadException(__FILE__, __LINE__, ex, "Transforms parse error");
            } catch ( const CLoadException & ex ) {
                throw ex;
            }
        }
    } catch (const CTokenException & e){
        throw CLoadException(__FILE__, __LINE__, e, "Error reading transforms.");
    }
}

void CWidget::render(const CBitmap & bitmap, const CFont & font){
    render(bitmap);
}
} //end SGF