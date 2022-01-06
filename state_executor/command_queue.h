#include <tbb/concurrent_queue.h>
#include <state_executor/i_command.h>

using CommandSP = std::shared_ptr<ICommand>;
using CommandQueue = tbb::concurrent_bounded_queue< CommandSP >;
