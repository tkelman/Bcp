// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
#include "BCP_lp_node.hpp"
#include "BCP_warmstart.hpp"
#include "BCP_USER.hpp"

#include "BCP_message.hpp"

BCP_lp_node::~BCP_lp_node()
{
    clean();
    purge_ptr_vector(*(dynamic_cast<BCP_vec<BCP_var*>*>(&vars)));
    purge_ptr_vector(*(dynamic_cast<BCP_vec<BCP_cut*>*>(&cuts)));
}

void
BCP_lp_node::clean()
{
    delete user_data; user_data = 0;
    delete cg;        cg = 0;
    delete cp;        cp = 0;
    delete vg;        vg = 0;
    delete vp;        vp = 0;
    delete warmstart; warmstart = 0;
    lb_at_cutgen.clear();
}

//#############################################################################

void
BCP_lp_parent::clean()
{
    added_vars_index.clear();
    added_vars_desc.clear();
    added_cuts_index.clear();
    added_cuts_desc.clear();
    delete warmstart;
    warmstart = 0;
}

BCP_lp_parent::~BCP_lp_parent()
{
    clean();
}

