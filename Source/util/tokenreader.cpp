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

#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include "util/SGF_Token.h"
#include "util/tokenreader.h"


using namespace std;
namespace SGF {

/* tokenreader reads a file formatted with s-expressions. examples:
 * (hello)
 * (hello world)
 * (hello "world")
 * (hello (world))
 * (hello (world hi))
 */

TokenReader::TokenReader(){
}
TokenReader::TokenReader( const char * file ){
	cout << "TokenReader::TokenReader( const char * file ) // Constructor //=> File: " << file << endl;
	ifile.open( file );
	myfile = string( file );
	ifile >> noskipws;
	// cout<<"Opened "<<file<<endl;
	cout << "TokenReader::TokenReader( const char * file ) // Opened //=> File: " << file << endl;

}

TokenReader::TokenReader( const string & file ){
	cout << "TokenReader::TokenReader( const char * file ) // Constructor //=> File: " << file << endl;
	
	ifile.open( file.c_str() );
	myfile = file;
	ifile >> noskipws;	

    cout << "TokenReader::TokenReader( const char * file ) // Opened //=> File: " << file << endl;

}
Token * TokenReader::readTokenFromFile(const std::string & file){
  
	ifile.open( file.c_str() );
	myfile = file;
	if (!ifile){
        ostringstream out;
        out << "Could not open '" << file << "'";
        throw CTokenException(__FILE__, __LINE__, out.str());
    }
	ifile >> noskipws;	
	return readToken();
/*    Filesystem::CAbsolutePath realPath(path);
    CReferenceCount<Filesystem::File> file = Storage::instance().open(realPath);
    if (file == NULL || !file->good()){
        throw CTokenException(__FILE__, __LINE__, string("Could not read ") + realPath.path());
    }
    readTokens(*file.raw());
    // file.close();
    if (my_tokens.size() > 0){
        my_tokens[0]->setFile(path);
        return my_tokens[0];
    }
    ostringstream out;
    out << "No tokens read from " << path;
    throw CTokenException(__FILE__, __LINE__, out.str());
	*/
}

TokenReader::~TokenReader(){
	cout << "TokenReader::~TokenReader() // Destructor //" << endl;
	
	ifile.close();

	/* tokenreader giveth, and tokenreader taketh */
	for ( vector< Token * >::iterator it = my_tokens.begin(); it != my_tokens.end(); it++ ){
		delete *it;
	}
    cout << "TokenReader::~TokenReader() // Closed File //" << endl;

}



Token * TokenReader::readToken() throw( CTokenException ){
 cout << "TokenReader::readToken() // BEGIN //" << endl;
	
	if ( !ifile ){
            throw CTokenException(__FILE__, __LINE__, string("Could not open ") + myfile );
        }
	// Token * t;

	// string token_string;

	char open_paren = 'x';
	int parens = 1;
	while ( ifile.good() && open_paren != '(' ){
		ifile >> open_paren;
	}
	// token_string += '(';
	//cout << "TokenReader::readToken() // PROCESS //" << "ifile read caracter: "<<open_paren << endl;
	cout << "TokenReader::readToken() // PROCESS //" << "Cria NEW Token" <<endl;
	
	Token * cur_token = new Token();
	cur_token->setFile( myfile );
	cout<<"TokenReader::readToken() // PROCESS // my_tokens.push_back( "<< cur_token << " )" <<endl;
			
	my_tokens.push_back( cur_token );
	Token * first = cur_token;
	
	vector< Token * > token_stack;
        /* tokens that were ignored using ;@, and should be deleted */
    vector<Token*> ignore_list;
	cout<<"TokenReader::readToken() // PROCESS // token_stack.push_back( "<< cur_token << " )" <<endl;
	
	token_stack.push_back( cur_token );

        /* when a ;@ is seen, read the next s-expression but throw it away */
        bool do_ignore = false;

	char n;
	string cur_string = "";
	// while ( parens != 0 ){
	
	/* in_quote is true if a " is read and before another " is read */
	bool in_quote = false;

	/* escaped unconditionally adds the next character to the string */
	bool escaped = false;
	while ( !token_stack.empty() ){
		if ( !ifile ){
			// cout<<__FILE__<<": "<<myfile<<" is bad. Open parens "<<parens<<endl;
			// cout<<"Dump: "<< token_string << "Last token = [" << n << "]" << (int)n << endl;
			// first->print( " " );
                        ostringstream failure;
                        failure << "Wrong number of parentheses. Open parens is " << parens;
			throw CTokenException(__FILE__, __LINE__,failure.str());
		}
		// char n;
		// slow as we go
		ifile >> n;
		
		const char * alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./-_!:";
		const char * nonalpha = " ;()#\"";
		//cout<<"TokenReader::readToken() // PROCESS // Alpha char: "<<n<<endl;
        //cout<<"TokenReader::readToken() // PROCESS // String : "<< cur_string <<endl;

		if ( escaped ){
                    switch (n){
                        case 'n' : {
                            cur_string += "\n";
                            break;
                        }
                        default : {
                            cur_string += n;
                            break;
                        }
                    }
                    escaped = false;
                    continue;
		}

		if ( n == '\\' ){
			escaped = true;
			continue;
		}

		if ( in_quote ){
			if ( n == '"' ){
				in_quote = false;
				//cout<<"TokenReader::readToken() // PROCESS // Made New Token quoted Char:" << n <<endl;
				cout<<"TokenReader::readToken() // PROCESS // Made New Token (in_quote) String:" << cur_string <<endl;
				Token * sub = new Token( cur_string, false );
				sub->setParent( cur_token );
                                if (do_ignore){
                                    ignore_list.push_back(sub);
                                    do_ignore = false;
                                } else {
                                    cur_token->addToken( sub );
                                }
				cur_string = "";

			} else
				cur_string += n;

		} else {
			if ( n == '"' )
				in_quote = true;
				
			if ( strchr( alpha, n ) != NULL ){
				cur_string += n;
			} else if ( cur_string != "" && strchr( nonalpha, n ) != NULL ){
				//cout<<"TokenReader::readToken() // PROCESS // Alpha char: "<<n<<endl;
                cout<<"TokenReader::readToken() // PROCESS // String : "<< cur_string <<endl;
                cout<<"TokenReader::readToken() // PROCESS // Made new (quoted)token "<<cur_string<<endl;
				Token * sub = new Token( cur_string, false );
				sub->setParent( cur_token );
                                if (do_ignore){
                                    do_ignore = false;
                                    ignore_list.push_back(sub);
                                } else {
                                    cur_token->addToken( sub );
                                }
				cur_string = "";
			}
		}

		if ( n == '#' || n == ';' ){
                    ifile >> n;
                    if (n == '@'){
                        do_ignore = true;
                    } else {
			while ( n != '\n' && !ifile.eof() ){
				ifile >> n;
			}
			continue;
                    }
		} else if ( n == '(' ){
			//cout<<"TokenReader::readToken() // PROCESS // Alpha char: "<<n<<endl;
            cout<<"TokenReader::readToken() // PROCESS // String : "<< cur_string <<endl;
            cout<<"TokenReader::readToken() // PROCESS // Made new (another) token "<<cur_string<<endl;
				
			Token * another = new Token();
			another->setParent( cur_token );

                        if (do_ignore){
                            ignore_list.push_back(another);
                            do_ignore = false;
                        } else {
                            cur_token->addToken(another);
                        }

			cur_token = another;
			cout<<"TokenReader::readToken() // PROCESS // token_stack.push_back( "<< cur_token << " )" <<endl;
			token_stack.push_back( cur_token );
			/*
			parens++;
			cout<<"Inc Parens is "<<parens<<endl;
			*/
		} else if ( n == ')' ){
			
			if ( token_stack.empty() ){
				cout<<"Stack is empty"<<endl;
				throw CTokenException(__FILE__, __LINE__,"Stack is empty");
			}
			cout<<"TokenReader::readToken() // PROCESS // Token_stack.popback() " <<endl;
            token_stack.pop_back();

			if ( ! token_stack.empty() ){
				cout<<"TokenReader::readToken() // PROCESS // Token_stack.back " <<endl;
            	cur_token = token_stack.back();
			}
		}
	}   //final bloco while stack not empty

        for (vector<Token*>::iterator it = ignore_list.begin(); it != ignore_list.end(); it++){
            delete (*it);
        }
	cout << "CTokenReaderXML::readToken() // PRINT //" << endl;
	
	 first->print("");
	first->finalize();
	
	cout << "CTokenReaderXML::readToken() // END //" << endl;
	return first;

}


Token * TokenReader::readTokenFromFile(Filesystem::File & file){
    readTokens(file);
    // file.close();
    if (my_tokens.size() > 0){
        my_tokens[0]->setFile("");
        return my_tokens[0];
    }
    ostringstream out;
    out << "No tokens read from file";
    throw CTokenException(__FILE__, __LINE__, out.str());

}
Token * TokenReader::readToken(const string & path){
    return readTokenFromFile(path);
}

Token * TokenReader::readToken(const char * path){
    return readTokenFromFile(path);
}
    
Token * TokenReader::readTokenFromString(const string & stuff){
    /*
    istringstream input(stuff);
    input >> noskipws;
    */
    Filesystem::StringFile input(stuff);
    readTokens(input);
    if (my_tokens.size() > 0){
        return my_tokens[0];
    }
    throw CTokenException(__FILE__, __LINE__, "No tokens read");
}

static inline bool is_alpha(char c){
    // const char * alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./-_!:*";
    const char * alpha = "./-_!:*";
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') ||
           strchr(alpha, c) != NULL;
}

static inline bool is_nonalpha(char c){
    const char * nonalpha = " ;()#\"";
    return strchr(nonalpha, c) != NULL;
}

class BufferedStream{
public:
    BufferedStream(Filesystem::File & input):
    data(NULL),
    position(0),
    size(input.getSize()){
        if (input.getSize() == 0){
            throw CTokenException(__FILE__, __LINE__, "File has size 0");
        }
        data = new unsigned char[size];
        input.readLine((char*) data, size);
    }

    BufferedStream & operator>>(unsigned char & n){
        if (position < size){
            n = data[position];
            position += 1;
        }
        return *this;
    }

    bool eof(){
        return position >= size;
    }

    ~BufferedStream(){
        delete[] data;
    }

    unsigned char * data;
    int position;
    int size;
};

void TokenReader::readTokens(Filesystem::File & input){

    /*
    if ( !ifile ){
        ostringstream out;
        out << "Could not open '" << myfile << "'";
        throw TokenException(__FILE__, __LINE__, out.str());
    }
    */
    // Token * t;

    // string token_string;

    // char open_paren = 'x';
    int parens = 0;
    // int position = 0;
    /*
    while (input.good() && open_paren != '('){
        input >> open_paren;
        position += 1;
    }
    */
    // token_string += '(';

    BufferedStream buffer(input);

    Token * currentToken = NULL;
    // Token * cur_token = new Token();
    // cur_token->setFile(myfile);
    // my_tokens.push_back(cur_token);
    // Token * first = cur_token;
    vector<Token *> token_stack;
    /* tokens that were ignored using ;@, and should be deleted */
    vector<Util::CReferenceCount<Token> > ignore_list;
    // token_stack.push_back(cur_token);

    /* when a ;@ is seen, read the next s-expression but throw it away */
    bool do_ignore = false;

    unsigned char n = 0;
    string cur_string = "";

    /* in_quote is true if a " is read and before another " is read */
    bool in_quote = false;

    /* escaped unconditionally adds the next character to the string */
    bool escaped = false;
    while (!buffer.eof()){
            // char n;
        // slow as we go
        buffer >> n;
        // position += 1;
        // printf("Read character '%c' %d at %d\n", n, n, input.tellg());
        // cout << "Read character '" << n << "' " << (int) n << " at " << input.tellg() << endl;

        // cout<<"Alpha char: "<<n<<endl;

        if (escaped){
            switch (n){
                case 'n' : {
                    cur_string += "\n";
                    break;
                }
                default : {
                    cur_string += n;
                    break;
                }
            }
            escaped = false;
            continue;
        }

        if (n == '\\'){
            escaped = true;
            continue;
        }

        if (in_quote){
            if (n == '"'){
                in_quote = false;

                Token * sub = new Token(cur_string, false);
                if (currentToken != NULL){
                    sub->setParent(currentToken);
                    if (do_ignore){
                        ignore_list.push_back(Util::CReferenceCount<Token>(sub));
                        do_ignore = false;
                    } else {
                        currentToken->addToken(sub);
                    }
                    cur_string = "";
                } else {
                    delete sub;
                }
            } else {
                cur_string += n;
            }
        } else {
            /* not in a quote */

            if (n == '"'){
                in_quote = true;
            } else if (is_alpha(n)){
                cur_string += n;
            } else if (cur_string != "" && is_nonalpha(n)){
                // cout<<"Made new token "<<cur_string<<endl;
                Token * sub = new Token(cur_string, false);
                if (currentToken != NULL){
                    sub->setParent(currentToken);
                    if (do_ignore){
                        do_ignore = false;
                        ignore_list.push_back(Util::CReferenceCount<Token>(sub));
                    } else {
                        currentToken->addToken(sub);
                    }
                } else {
                    delete sub;
                }
                cur_string = "";
            }

            if (n == '#' || n == ';'){
                buffer >> n;

                /* if the next character is a @ then ignore the next entire s-expression
                 * otherwise just ignore the current line
                 */
                if (n == '@'){
                    do_ignore = true;
                } else {
                    while (n != '\n' && !buffer.eof()){
                        buffer >> n;
                    }
                    continue;
                }
            } else if (n == '('){
                Token * another = new Token();
                if (currentToken != NULL){
                    another->setParent(currentToken);
                }

                if (do_ignore){
                    ignore_list.push_back(Util::CReferenceCount<Token>(another));
                    do_ignore = false;
                } else {
                    if (currentToken != NULL){
                        currentToken->addToken(another);
                    } else {
                        /* top level token */
                        my_tokens.push_back(another);
                    }
                }

                parens += 1;
                currentToken = another;
                token_stack.push_back(currentToken);
            } else if (n == ')'){
                parens -= 1;
                if (token_stack.empty()){
                    throw CTokenException(__FILE__, __LINE__, "Saw a ) but there is no corresponding (");
                }
                token_stack.pop_back();

                if (! token_stack.empty()){
                    currentToken = token_stack.back();
                } else {
                    currentToken = NULL;
                }
            }
        }
    }

    if (!token_stack.empty()){
        ostringstream failure;
        failure << "Wrong number of parentheses. Open parens is " << parens;
        throw CTokenException(__FILE__, __LINE__, failure.str());
    }

    /*
    for (vector<Token*>::iterator it = my_tokens.begin(); it != my_tokens.end(); it++){
        Token * token = *it;
        token->finalize();
    }
    */
}

} //end SGF