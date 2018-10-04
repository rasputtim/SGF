#include "util/SGF_UtilStructs.h"
#include <stdio.h>
#include "graphics/all.h"
#include "util/SGF_Debug.h"
using namespace std;

namespace SGF {




SDLState::SDLState(int numWindows):
flags(0),
verbose(0),

/* Video info */
videodriver(NULL),
display(0),
Scaler(NULL),
Buffer(NULL),
depth(32),
refresh_rate(0),
num_windows(numWindows),

/* Renderer info */
renderdriver(NULL),
render_flags(0),
skip_renderer(SDL_FALSE),

/* Audio info */
audiodriver(NULL),

/* GL settings */
gl_red_size(3),
gl_green_size(3),
gl_blue_size(2),
gl_alpha_size(0),
gl_buffer_size(0),
gl_depth_size(16),
gl_stencil_size(0),
gl_double_buffer(1),
gl_accum_red_size(0),
gl_accum_green_size(0),
gl_accum_blue_size(0),
gl_accum_alpha_size(0),
gl_stereo(0),
gl_multisamplebuffers(0),
gl_multisamplesamples(0),
gl_retained_backing(1),
gl_accelerated(-1),
gl_major_version(2),
gl_minor_version(1){
window_infos = (windowInfo_s **) malloc(numWindows *
                                    sizeof(*window_infos));
for (int i=0; i< numWindows;i++) {

    window_infos[i]= new windowInfo_s();
}
windows = (SDL_Window **) malloc(numWindows *
                                    sizeof(*windows));
renderers = (SDL_Renderer **) SDL_malloc(numWindows *
                                    sizeof(*renderers));
Screen = (CBitmap **) SDL_malloc(numWindows *
                                    sizeof(*Screen));

     if (!window_infos || !windows || !renderers|| !Screen) {
        Debug::debug(Debug::error,__FUNCTION__) << "Out of memory" <<endl;
        //return NULL;
    }

audiospec.freq = 22050;
audiospec.format = AUDIO_S16;
audiospec.channels = 2;
audiospec.samples = 2048;


}


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
