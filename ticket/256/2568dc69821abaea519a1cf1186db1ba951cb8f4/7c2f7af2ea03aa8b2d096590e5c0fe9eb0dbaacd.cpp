#define BOOST_TEST_MODULE Test wxString::Format
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp> // for function-like macro BOOST_DATA_TEST_CASE
#include <wx/wx.h>

namespace nsData = boost::unit_test::data;
BOOST_DATA_TEST_CASE(
	test_string_format,
	nsData::xrange<int>((
		nsData::begin = 65'000,
		nsData::end = 65'540,
		nsData::step = 1
	)),
	LENGTH
) {
	wxString veryLongString('.', LENGTH);
	BOOST_TEST(veryLongString.length() == LENGTH);
	BOOST_TEST(wxString::Format("%s", veryLongString) == veryLongString);
}
