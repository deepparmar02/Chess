#include "move.h"

Move::Move(char start_file, int start_rank, char end_file, int end_rank)
    : start_file{start_file}, start_rank{start_rank}, end_file{end_file},
      end_rank{end_rank}, promote_to{' '}
{}

Move::Move(char start_file, int start_rank, char end_file, int end_rank, char promote_to) 
    : start_file{start_file}, start_rank{start_rank}, end_file{end_file},
      end_rank{end_rank}, promote_to{promote_to}
{}

Move::Move() :
  start_file{'\0'}, start_rank{0}, end_file{'\0'}, end_rank{0}, promote_to{' '}
{}

Move::~Move() {}