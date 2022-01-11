#ifndef __WXSTRISTR_H__
#define __WXSTRISTR_H__

#include <wx/wxchar.h>

const wxChar* wxStristr(const wxChar* string, const wxChar* strSearch)
     {
     if (!string)
          {
          return NULL;
          }
     size_t substring_len = ::wxStrlen_(strSearch);
     size_t string_len = ::wxStrlen_(string);
     while (string)
          {
          if (string_len < substring_len)
               {
               return NULL;
               }
          //compare the characters one at a time
          size_t i = 0;
          for (i = 0; i < substring_len; ++i)
               {
               if (::wxTolower(strSearch[i]) != ::wxTolower(string[i]) )
                    {
                    ++string;
                    --string_len;
                    break;
                    }
               }
          //if the substring loop completed then the substring was found
          if (i == substring_len)
               {
               return string;
               }
          }
     return NULL;
     }


#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/CompilerOutputter.h>
//Unit Tests for wxStristr
class StrIStrTest : public CppUnit::TestFixture
     {
public:
     CPPUNIT_TEST_SUITE(StrIStrTest);
        CPPUNIT_TEST(TestFindFirstItem);
        CPPUNIT_TEST(TestLastItemInSequenceString);
        CPPUNIT_TEST(TestFindNothing);
        CPPUNIT_TEST(TestEmptyString);
        CPPUNIT_TEST(TestSubStringTooBig);
     CPPUNIT_TEST_SUITE_END();

     void TestFindFirstItem()
        {
        char buffer[] = "hello, world";
        //should find at the beginning
        CPPUNIT_ASSERT(wxStristr(buffer, "HelLo") == buffer);
        }
     void TestLastItemInSequenceString()
        {
        char buffer[] = "hello, world";
        //should find last item in sequence
        CPPUNIT_ASSERT(wxStristr(buffer, "WORLD") == buffer+7);        
        }
     void TestFindNothing()
        {
        char buffer[] = "hello, world";
        //should find nothing and return NULL
        CPPUNIT_ASSERT(wxStristr(buffer, "Help") == NULL);
        }
     void TestEmptyString()
        {
        //should find nothing and NULL
        CPPUNIT_ASSERT(wxStristr("", "Hello") == NULL);
        }
     void TestSubStringTooBig()
        {
        CPPUNIT_ASSERT(wxStristr("Hello", "Hello World") == NULL);
        }
     };

#endif //__WXSTRISTR_H__

 	  	 
