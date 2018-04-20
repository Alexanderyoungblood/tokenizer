/*-
 * Copyright 2014-2018 Diomidis Spinellis
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#ifndef TOKENIZERBASE_H
#define TOKENIZERBASE_H

#include <iostream>
#include <sstream>

#include "CharSource.h"
#include "CKeyword.h"
#include "BolState.h"

/** Collect quality metrics from C-like source code */
class TokenizerBase {
protected:
	std::stringstream string_src;	// Source for testing
	CharSource src;			// Character source
	/** True for keywords that don't end with semicolon */
	bool saw_comment;		// True after a comment
	/** Called at every encountered newline */
	void newline(bool in_non_code_block = false) {}
	BolState bol;			// Beginning of line state
public:
	virtual int get_token() = 0;	// Return a single token
	void tokenize();		// Tokenize to stdout

	// Construct from a character source
	TokenizerBase(CharSource &s) : src(s), saw_comment(false) {}

	// Construct for a string source
	TokenizerBase(const std::string &s) : string_src(s), src(string_src),
	saw_comment(false) {}

	~TokenizerBase();

	static int num_token(const std::string &val);
	bool process_block_comment();
	bool process_line_comment();
	bool process_char_literal();
	bool process_string_literal();
	int process_number(std::string &val);
};
#endif /* TOKENIZERBASE_H */
