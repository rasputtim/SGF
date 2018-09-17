#include <string>
#include "util/SGF_LanguageString.h"
#include "configuration/SGF_Configuration.h"

using namespace std;
namespace SGF {

CLanguageString::CLanguageString(){
}

CLanguageString::CLanguageString(const string & stuff){
    add(stuff);
}

CLanguageString::CLanguageString(const char * stuff){
    add(stuff);
}

CLanguageString::CLanguageString(const string & stuff, const string & language){
    add(stuff, language);
}

CLanguageString::CLanguageString(const CLanguageString & language){
    languages = language.languages;
}

CLanguageString & CLanguageString::operator=(const CLanguageString & obj){
    this->languages = obj.languages;
    return *this;
}

void CLanguageString::add(const string & stuff, const string & language){
    languages[language] = stuff;
}

void CLanguageString::add(const string & stuff){
    add(stuff, defaultLanguage());
}
 const string CLanguageString::currentLanguage() const {
    return CConfiguration::gameLanguage.getString();
}
const string & CLanguageString::get() const{
    map<string, string>::const_iterator find = languages.find(currentLanguage());
    if (find != languages.end()){
        return find->second;
    }
    find = languages.find(defaultLanguage());
    if (find != languages.end()){
        return find->second;
    }
    return "";

}
} //end SGF