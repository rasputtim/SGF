#include "util/SGF_UtilStructs.h"
#include <stdio.h>
#include "graphics/all.h"
using namespace std;

namespace SGF {

SDLState::~SDLState(){
if (Scaler!=NULL){ delete Scaler; Scaler=NULL;}
if (Buffer!=NULL){ delete Buffer; Buffer=NULL;}
if (renderdriver!=NULL){ delete renderdriver; renderdriver=NULL;}
if (audiodriver!=NULL){ delete audiodriver; audiodriver=NULL;}
if (videodriver!=NULL){ delete videodriver; videodriver=NULL;}

if (window_infos) {
    free(window_infos);
}

if (windows) {

    for (int i = 0; i < num_windows; ++i) {
        if (windows[i]) {
            SDL_DestroyWindow(windows[i]);
        }
    }
    SDL_free(windows);
}

if (renderers) {
    for (int i = 0; i < num_windows; ++i) {
        if (renderers[i]) {
            SDL_DestroyRenderer(renderers[i]);
        }
    }
    SDL_free(renderers);
}



for (int i =0 ;i < num_windows; i++) if (Screen[i]) {delete Screen[i]; Screen[i]=NULL;}
if(Screen) ::SDL_free(Screen);


}

} //end SGF
