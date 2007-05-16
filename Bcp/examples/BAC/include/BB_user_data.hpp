// Last edit: 2/10/05
//
// Name:     BB_user_data.hpp
// Author:   Francois Margot
//           Tepper School of Business
//           Carnegie Mellon University, Pittsburgh, PA 15213
//           email: fmargot@andrew.cmu.edu
// Date:     12/28/03
//-----------------------------------------------------------------------------
// Copyright (C) 2003, Francois Margot. All Rights Reserved.

#ifndef _BB_UD_H
#define _BB_UD_H

#include "BCP_USER.hpp"

class BCP_buffer;

/**Class handling user data */

/**************************************************************************/
class real_user_data {

  /* Add: fields for real_user_data */

public:

  //@name Public data members */
  //@{
  /// Maximum number of variables that may be set to zero by branching
  /// decisions
  int max_card_set_zero;

  /// Number of variables set to zero by branching descisions 
  int card_set_zero;
  
  /// Variables that have been set to zero by branching decisions
  int *set_zero;
  //@}

  /**@name Constructors and destructors */
  //@{
  /// Constructor 
  real_user_data(const int max_size);

  /// Desctructor
  ~real_user_data();
  //@}

  /// Dump the fields of the class
  void print() const;
};

/** Class taking care of interaction between user data and Bcp */

/**************************************************************************/
class MY_user_data : public BCP_user_data {
public:

  /// Indicator for mmory management: If is_processed = 1, the associated 
  /// user data may be erased
  int is_processed;

  /// Pointer on an object holding the user data itself
  real_user_data *p_rud;

public:

  /**@name Constructors and destructors */
  //@{
  /// Initial constructor 
  MY_user_data(const int max_size);

  /// Constructor from buffer content
  MY_user_data(BCP_buffer& buf);

  /// Destructor
  ~MY_user_data();

  /// Packing  to buffer
  void pack(BCP_buffer& buf) const;

  /// Dump the fields of the class
  void print() const;
};

/**************************************************************************/
/** Class taking care of packing/unpacking */

class BB_packer : public BCP_user_pack {
public:
    //-------------------------------------------------------------------------
    /** Pack warmstarting information */
    virtual void
    pack_warmstart(const BCP_warmstart* ws, BCP_buffer& buf,
		   bool report_if_default = false)
    {
	if (report_if_default) {
	    printf("BCP_user_pack : default pack_warmstart() executed.\n");
	}
	BCP_pack_warmstart(ws, buf);
    }

    /** Unpack warmstarting information */
    virtual BCP_warmstart*
    unpack_warmstart(BCP_buffer& buf,
		     bool report_if_default = false)
    {
	if (report_if_default) {
	    printf("BCP_user_pack : default unpack_warmstart() executed.\n");
	}
	return BCP_unpack_warmstart(buf);
    }
    
    //-------------------------------------------------------------------------
    /** Pack an algorithmic variable */
    virtual void
    pack_var_algo(const BCP_var_algo* var, BCP_buffer& buf)
    {
	throw BCP_fatal_error("\
BCP_user_pack::pack_var_algo() invoked but not overridden!\n");
    }

    /** Unpack an algorithmic variable */
    virtual BCP_var_algo* unpack_var_algo(BCP_buffer& buf)
    {
	throw BCP_fatal_error("\
BCP_user_pack::unpack_var_algo() invoked but not overridden!\n");
	return 0; // to satisfy aCC on HP-UX
    }
      
    //-------------------------------------------------------------------------
    /** Pack an algorithmic cut */
    virtual void pack_cut_algo(const BCP_cut_algo* cut, BCP_buffer& buf);

    /** Unpack an algorithmic cut */
    virtual BCP_cut_algo* unpack_cut_algo(BCP_buffer& buf);

    //-------------------------------------------------------------------------
    /** Pack an user data */
    virtual void pack_user_data(const BCP_user_data* ud, BCP_buffer& buf);

    /** Unpack an user data */
    virtual BCP_user_data* unpack_user_data(BCP_buffer& buf);
};


#endif


