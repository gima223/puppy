#include <fstream>
#include <thread>
#include <stdexcept>
#include <string>
#include <iostream>

#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/lambda/lambda.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace logging = boost::log;
namespace sinks = logging::sinks;
namespace src = boost::log::sources;
namespace keywords = logging::keywords;
namespace expr = boost::log::expressions;

typedef sinks::synchronous_sink<sinks::text_file_backend> sink_t;

void handler1(sinks::text_file_backend::stream_type &file)
{
  std::cout << "Opened" << std::endl;
}

void handler2(sinks::text_file_backend::stream_type &file)
{
  std::cout << "Closed" << std::endl;
}

boost::shared_ptr<sink_t> init1()
{

  boost::shared_ptr<logging::core> core = logging::core::get();

  boost::shared_ptr<sinks::text_file_backend> backend =
      boost::make_shared<sinks::text_file_backend>(
          keywords::file_name = "file.log", //"file_%H%M%S_%N.log"
          keywords::target_file_name = "file_%H%M%S.log",
          keywords::rotation_size = 5 * 1024,
          keywords::enable_final_rotation = true,
          //keywords::open_mode = std::ios_base::out | std::ios_base::app,
          //keywords::time_based_rotation = sinks::file::rotation_at_time_point(12, 0, 0),
          keywords::time_based_rotation = sinks::file::rotation_at_time_interval(boost::posix_time::hours(1)));
  boost::shared_ptr<sink_t> sink(new sink_t(backend));
  sink->set_formatter(
      expr::format("%1%:[%2%]:%3%") % expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S") % logging::trivial::severity % expr::smessage);

  // Set header and footer writing functors
  sink->locked_backend()->set_open_handler(&handler1);
  sink->locked_backend()->set_close_handler(&handler2);

  sink->locked_backend()->set_file_collector(sinks::file::make_collector(
      keywords::target = "./",
      keywords::max_files = 3));
  // Upon restart, scan the directory for files matching the file_name pattern
  sink->locked_backend()->scan_for_files(sinks::file::scan_matching, "file_%H%M%S.log.txt");
  core->add_sink(sink);
  return sink;
}

int main(int argc, char const *argv[])
{

  boost::shared_ptr<sink_t> sink1 = init1();
  logging::add_common_attributes();
  using namespace logging::trivial;
  src::severity_logger<severity_level> lg;
  BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
  BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
  BOOST_LOG_TRIVIAL(info) << "An informational severity message";
  BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
  BOOST_LOG_TRIVIAL(error) << "An error severity message";
  BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
  BOOST_LOG_SEV(lg, trace) << "-----------------------";
  boost::shared_ptr<logging::core> core = logging::core::get();
  //core->remove_sink(sink1);
  std::this_thread::sleep_for(std::chrono::seconds(2)); // 1秒
  std::cout << "[Test] filename: " << sink1->locked_backend()->get_current_file_name() << std ::endl;
  bool tag = true;
  while (tag)
  {
    BOOST_LOG_SEV(lg, trace) << "A trace severity message";
    BOOST_LOG_SEV(lg, debug) << "A debug severity message";
    BOOST_LOG_SEV(lg, info) << "An informational severity message";
    BOOST_LOG_SEV(lg, warning) << "A warning severity message";
    BOOST_LOG_SEV(lg, error) << "An error severity message";
    BOOST_LOG_SEV(lg, fatal) << "A fatal severity message";
    //std::this_thread::sleep_for(std::chrono::seconds(1)); // 1秒
    tag = false;
  }
  return 0;
}

/*
b2 --build-dir=./ toolset=gcc stage
*/