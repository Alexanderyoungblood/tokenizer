#ifndef SYMBOLTABLETEST_H
#define SYMBOLTABLETEST_H

#include <cppunit/extensions/HelperMacros.h>

#include "SymbolTable.h"
#include "TokenId.h"

class SymbolTableTest : public CppUnit::TestFixture  {
	CPPUNIT_TEST_SUITE(SymbolTableTest);
	CPPUNIT_TEST(testSingle);
	CPPUNIT_TEST(testScope);
	CPPUNIT_TEST_SUITE_END();
public:
	void testSingle() {
		SymbolTable s;

		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER, s.symbol_value("foo"));
		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER, s.symbol_value("foo"));
		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER + 1, s.symbol_value("bar"));
		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER + 1, s.symbol_value("bar"));
		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER, s.symbol_value("foo"));
	}

	void testScope() {
		SymbolTable s;

		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER, s.symbol_value("foo"));

		s.enter_scope();
		// Look value at outer scope
		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER, s.symbol_value("foo"));
		// New entry at inner scope
		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER + 1, s.symbol_value("bar"));
		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER + 1, s.symbol_value("bar"));

		s.exit_scope();
		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER, s.symbol_value("foo"));
		// New entry at outer scope
		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER + 2, s.symbol_value("bar"));
		s.enter_scope();
		// Lookup at outer scope
		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER, s.symbol_value("foo"));
		CPPUNIT_ASSERT_EQUAL(TokenId::IDENTIFIER + 2, s.symbol_value("bar"));
	}
};
#endif /*  SYMBOLTABLETEST_H */
