#include <wx/hash.h>

int wxCALLBACK wxDataViewListModelSortedDefaultCompare
      (unsigned int row1, unsigned int row2, unsigned int col, wxDataModel* model )
{
//  static const long hash_string   = wxHashTableBase::MakeKey(wxT("string")); not needed
    static const long hash_long     = wxHashTableBase::MakeKey(wxT("long"));
    static const long hash_double   = wxHashTableBase::MakeKey(wxT("double"));
    static const long hash_datetime = wxHashTableBase::MakeKey(wxT("datetime"));

    auto   const long hash          = wxHashTableBase::MakeKey(model->GetColType(col));

    if (   (hash == hash_long)
        || (hash == hash_double)
        || (hash == hash_datetime)
       )
    {
        wxVariant value1,value2;
        model->GetValue( value1, col, row1 );
        model->GetValue( value2, col, row2 );

        if (hash == hash_long) // long
        {
            const long l1 = value1.GetLong();
            const long l2 = value2.GetLong();
            return l1-l2;
        }
        else if (hash == hash_double) // double
        {
            const double d1 = value1.GetDouble();
            const double d2 = value2.GetDouble();
            if (d1 == d2) return 0;
            if (d1 < d2) return 1;
            return -1;
        }
        else // hash_datetime
        {
            const wxDateTime dt1 = value1.GetDateTime();
            const wxDateTime dt2 = value2.GetDateTime();
            if (dt1.IsEqualTo(dt2)) return 0;
            if (dt1.IsEarlierThan(dt2)) return 1;
            return -1;
        }
    }
    else // string or unknown
    {
        wxString str1;
        wxString str2;
        model->GetValue( &str1, col, row1 );
        model->GetValue( &str2, col, row2 );
        return str1.Cmp( str2 );
    }
}


 	  	 
