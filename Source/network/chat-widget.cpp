#include <deque>
#include "graphics/all.h"
#include "input/all.h"
#include "network\SGF_Network.h"
#include "network/SGF_NetChatWidget.h"
#include "game/SGF_Theater.h"
#include "util/SGF_FontSystem.h"
#include "resource/all.h"
#include "util/SGF_FileSystem.h"
#include <string>

using namespace std;
namespace SGF {
static void do_finish_chat_input(void * arg){
    CChatWidget * widget = (CChatWidget *) arg;
    widget->endChatLine();
}

CChatWidget::CChatWidget(CTheater & world, CObject::networkid_t id):
world(world),
removeChatTimer(0),
enable_chat(false),
id(id){
    input.set(CKeyboard::Key_T, 0, false, Talk);
    chatInput.setBlockingKeys();
    chatInput.addBlockingHandle(CKeyboard::Key_ENTER, do_finish_chat_input, this);
}

CChatWidget::~CChatWidget(){
}

void CChatWidget::act(){
    vector<CInputMap<Inputs>::InputEvent> events = CInputManager::getEvents(input);

    for (vector<CInputMap<Inputs>::InputEvent>::iterator it = events.begin(); it != events.end(); it++){
        const CInputMap<Inputs>::InputEvent & event = *it;
        if (!event.enabled){
            continue;
        }

        /* This prevents 't' from being pressed in the chat thing immediately */
        if (event[Talk]){
            enable_chat = true;
        } else {
            if (enable_chat){
                chatInput.enable();
                enable_chat = false;
            }
        }
    }
    
    for (deque<Message>::iterator it = chatMessages.begin(); it != chatMessages.end();){
        Message & message = *it;
        message.life -= 1;
        if (message.life <= 0){
            it = chatMessages.erase(it);
        } else {
            it++;
        }
    }

    chatInput.doInput();
}

void CChatWidget::endChatLine(){
    string message = chatInput.getText();
    chatInput.disable();
    chatInput.clearInput();

    if (message != ""){
        Network::Message chat;
        /* server's id is always 0 */
        chat.id = 0;
        chat << CTheater::CHAT;
        chat << id;
        chat << message;
        //s world.addMessage(chat);
        receiveMessage(string("You: ") + message);
    }
}

void CChatWidget::receiveMessage(string message){
    chatMessages.push_back(Message("", message, 500));
    while (chatMessages.size() > 20){
        chatMessages.pop_front();
    }
    CResource::getSound(Filesystem::CRelativePath("menu/sounds/talk.wav"))->play();
}

void CChatWidget::drawChat(CBitmap * work, int start){
    const CFont & font = CFont::getFont(string(Global::DEFAULT_FONT), 18, 18);
    CFontRender * render = CFontRender::getInstance();

    // int y = work->getHeight() * 2 - 1 - font.getHeight() * 2 - 1;
    int y = start - font.getHeight();

    if (chatInput.isEnabled()){
        // render->addMessage(font, 1, y, green, -1, string("Say: ") + chatInput.getText());
		render->addMessage(font, 1, y, Colors::Yellow, Colors::DefaultColorkey, string("Say: "));
        render->addMessage(font, 1 + font.getTextLength("Say: "), y, Colors::Green, Colors::DefaultColorkey, chatInput.getText());
        y -= font.getHeight() + 1;
    }

    for (deque<Message>::reverse_iterator it = chatMessages.rbegin(); it < chatMessages.rend(); it++){
        const Message & message = *it;
        int trans = message.life;
        if (trans < 255){
            render->addMessage(font, 1, y, Colors::White, Colors::DefaultColorkey, trans, message.text);
        } else {
            render->addMessage(font, 1, y, Colors::White, Colors::DefaultColorkey, message.text);
        }
        y -= font.getHeight() + 1;
    }
}
} //end SGF