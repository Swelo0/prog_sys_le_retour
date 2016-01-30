#ifndef _PFS_H_
#define _PFS_H_

//////////////////////////////////////////////////////////////////////////////////////////
/// \file fs.h
/// \author Thierry Mourao
/// \author Sylvain Thullen
/// \author Sacha Conti
/// \date 27 décembre 2015
/// \brief Implementation of the kernel file system handling functions
//////////////////////////////////////////////////////////////////////////////////////////
#include "../common/pfs_common.h"
#include "ide.h"
#include "string.h"
#include "io.h"

int strcmp (const char* s1, const char* s2);

int file_stat(char* filename, stat_t* stat);

int file_read(char* filename, void* buf);

int file_remove(char* filename);

int file_exists(char* filename);

file_iterator_t file_iterator();

int file_next(char* filename, file_iterator_t* it);

#endif