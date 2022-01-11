
    //
    // Test wxVariant reference counting integrity
    // * Creates list of common wxVariant types.
    // * Creates other lists of slightly different size,
    //   but using values from the first list (ie. to
    //   create lots of references).
    // * Tests that the values in all lists have
    //   correct values, and that their wxVariantDatas
    //   are what they are supposed to (regarding
    //   refcounting).
    // * Assigns different values into second list.
    // * Tests that values in the first list are infact
    //   unmodified.

    wxVariant list;
    list.NullList();

    wxString stringVal = wxT("String");
    long longVal = 12345;
    double doubleVal = 12345.678;
    wxObject* wxObjectVal = &list;
    void* voidVal = (void*) &stringVal;
    wxDateTime dtVal = wxDateTime::Now();

    wxArrayString arrstrVal;
    arrstrVal.Add(wxT("item 1"));
    arrstrVal.Add(wxT("item 2"));
    arrstrVal.Add(wxT("item 3"));

    #define MAX_LISTS   5

    int listNum;
    int a;

    wxVariant lists[MAX_LISTS];

    wxVariant list0;
    list0.NullList();

    for ( a=0; a<10; a++ )
    {
        list0.Append( stringVal );
        list0.Append( longVal );
        list0.Append( doubleVal );
        list0.Append( wxObjectVal );
        list0.Append( voidVal );
        list0.Append( dtVal );
        list0.Append( arrstrVal );
    }

    lists[0] = list0;

    wxVariant* prevpList = &list0;


    // Creates new lists using values from the
    // original list, but at slightly different
    // positions.
    for ( listNum=1; listNum<MAX_LISTS; listNum++ )
    {
        wxVariant list;
        list.NullList();

        int a;
        int a0 = (4+listNum);
        int aMax = prevpList->GetCount() - ((4+listNum)*2);

        for ( a=a0; a<aMax; a++ )
        {
            list.Append(list0[a]);
        }

        lists[listNum] = list;
        prevpList = &lists[listNum];
    }


    // Test values and refDatas of created lists.
    for ( listNum=1; listNum<MAX_LISTS; listNum++ )
    {
        wxVariant list = lists[listNum];

        int a;
        int a0 = (4+listNum);

        for ( a=0; a<(int)list.GetCount(); a++ )
        {
            int i2 = (a+a0) % 7;
            if ( i2 == 0 )
            {
                wxASSERT( list[a] == stringVal );
            }
            else if ( i2 == 1 )
            {
                wxASSERT( list[a] == longVal );
            }
            else if ( i2 == 2 )
            {
                wxASSERT( list[a] == doubleVal );
            }
            else if ( i2 == 3 )
            {
                wxASSERT( list[a] == wxObjectVal );
            }
            else if ( i2 == 4 )
            {
                wxASSERT( list[a] == voidVal );
            }
            else if ( i2 == 5 )
            {
                wxASSERT( list[a] == dtVal );
            }
            /*else if ( i2 == 6 )
            {
                wxASSERT( list[a] == arrVal );
            }*/

            // Test m_refData
            wxASSERT( list[a].GetData() == list0[a+a0].GetData() );
        }

    }


    // Assignment operator test.
    wxVariant list1 = lists[1];
    for ( a=0; a<(int)list1.GetCount(); a++ )
    {
        int i2 = a % 7;
        if ( i2 == 0 )
            list1[a] = arrstrVal;
        else if ( i2 == 1 )
            list1[a] = dtVal;
        else if ( i2 == 2 )
            list1[a] = voidVal;
        else if ( i2 == 3 )
            list1[a] = wxObjectVal;
        else if ( i2 == 4 )
            list1[a] = doubleVal;
        else if ( i2 == 5 )
            list1[a] = longVal;
        else if ( i2 == 6 )
            list1[a] = stringVal;
    }


    // Test that the values of original list are intact
    for ( a=0; a<(int)list0.GetCount(); a++ )
    {
        int i2 = a % 7;
        if ( i2 == 0 )
            wxASSERT( list0[a] == stringVal );
        else if ( i2 == 1 )
            wxASSERT( list0[a] == longVal );
        else if ( i2 == 2 )
            wxASSERT( list0[a] == doubleVal );
        else if ( i2 == 3 )
            wxASSERT( list0[a] == wxObjectVal );
        else if ( i2 == 4 )
            wxASSERT( list0[a] == voidVal );
        else if ( i2 == 5 )
            wxASSERT( list0[a] == dtVal );
        /*else if ( i2 == 6 )
            wxASSERT( list0[a] == arrVal );*/
    }

 	  	 
