#!/usr/bin/perl
#############################################################################
## Name:        samples/dialog/dialog.pl
## Purpose:     Dialog wxPerl sample
## Author:      Mattia Barbon
## Modified by:
## Created:     12/11/2000
## RCS-ID:      $Id: dialog.pl,v 1.4 2004/10/19 20:28:13 mbarbon Exp $
## Copyright:   (c) 2000 Mattia Barbon
## Licence:     This program is free software; you can redistribute it and/or
##              modify it under the same terms as Perl itself
#############################################################################

BEGIN { use File::Basename; unshift( @INC, ( File::Basename::dirname($0))) }

use Wx;

package MyApp;

use strict;
use vars qw(@ISA);

@ISA=qw(Wx::App);

use strict;
use Wx qw( wxDefaultSize wxDefaultPosition wxID_OK wxID_SAVE wxID_SAVEAS wxID_CANCEL wxID_YES wxID_EXIT wxID_ABOUT wxID_HELP );
use Wx qw( wxVERTICAL wxHORIZONTAL wxALL wxLEFT wxRIGHT wxTOP wxBOTTOM wxCENTRE wxGROW wxADJUST_MINSIZE );
use Wx qw( wxALIGN_RIGHT wxALIGN_BOTTOM wxALIGN_CENTER wxALIGN_CENTER_VERTICAL wxALIGN_CENTER_HORIZONTAL wxALIGN_CENTRE wxLC_REPORT wxSUNKEN_BORDER wxLC_HRULES wxLC_VRULES);
use Wx qw(wxDefaultSize wxDefaultPosition);
use Wx::Event qw(EVT_BUTTON EVT_CLOSE EVT_CHOICE EVT_COMBOBOX EVT_RADIOBOX EVT_CHECKBOX EVT_LISTBOX EVT_LIST_ITEM_SELECTED EVT_CHECKLISTBOX);

sub OnInit 
{
   my( $this ) = @_;
   my $dialog_ptr = Wx::Dialog->new(undef, -1, "First Dialog");
   my $item3   = Wx::StaticBox->new(  $dialog_ptr, -1, "" );
   my $item301 = Wx::Choice->new( $dialog_ptr, 301, wxDefaultPosition,[150,-1], 
      [
         "×"
      ] , 0 );
   ##
   my $item2 = Wx::StaticBoxSizer->new( $item3, wxHORIZONTAL );
      $item2->Add( $item301, 0, wxALIGN_CENTER|wxALL, 0 );
   ##
   my $item0 = Wx::BoxSizer->new( wxVERTICAL );
      $item0->Add( $item2, 0, wxALIGN_CENTER|wxALL, 0 );
   ##
   my( $set_size ) = @_ >= 3 ? $_[2] : 1;
   my( $call_fit ) = @_ >= 2 ? $_[1] : 1;
   if( $set_size == 1 ) 
   {
   $dialog_ptr->SetSizer( $item0 );
   $item0->SetSizeHints( $dialog_ptr ) if( $call_fit == 1 );
   }

   my $return_value = $dialog_ptr->ShowModal();
##      $dialog_ptr->Destroy();
}

package main;

my( $app ) = MyApp->new();

$app->MainLoop();

# Local variables: #
# mode: cperl #
# End: #


 	  	 
