/* $Id: templateengine.py 2241 2006-05-22 07:58:58Z fischer $ */

///
/// @file        UnicastSocketTest.hh
/// @brief       CPPUnit-Tests for class UnicastSocket
/// @author      Author Name (email@mail.address)
/// @date        Created at 2010-11-01
/// 
/// @version     $Revision: 2241 $
/// @note        Last modification: $Date: 2006-05-22 09:58:58 +0200 (Mon, 22 May 2006) $
///              by $Author: fischer $
///

 
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#ifndef UNICASTSOCKETTEST_HH
#define UNICASTSOCKETTEST_HH
class UnicastSocketTest : public CppUnit::TestFixture {
	private:
	public:
		/*=== BEGIN tests for class 'UnicastSocket' ===*/
		void testBind();
		/*=== END   tests for class 'UnicastSocket' ===*/

		void setUp();
		void tearDown();


		CPPUNIT_TEST_SUITE(UnicastSocketTest);
			CPPUNIT_TEST(testBind);
		CPPUNIT_TEST_SUITE_END();
};
#endif /* UNICASTSOCKETTEST_HH */
