// Lv2Grpc.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>

#include <grpcpp/grpcpp.h>
#include <proxy.grpc.pb.h>

#pragma comment(lib, "absl_bad_any_cast_impl.lib")
#pragma comment(lib, "absl_bad_optional_access.lib")
#pragma comment(lib, "absl_bad_variant_access.lib")
#pragma comment(lib, "absl_base.lib")
#pragma comment(lib, "absl_city.lib")
#pragma comment(lib, "absl_civil_time.lib")
#pragma comment(lib, "absl_cord.lib")
#pragma comment(lib, "absl_cord_internal.lib")
#pragma comment(lib, "absl_cordz_functions.lib")
#pragma comment(lib, "absl_cordz_handle.lib")
#pragma comment(lib, "absl_cordz_info.lib")
#pragma comment(lib, "absl_cordz_sample_token.lib")
#pragma comment(lib, "absl_debugging_internal.lib")
#pragma comment(lib, "absl_demangle_internal.lib")
#pragma comment(lib, "absl_examine_stack.lib")
#pragma comment(lib, "absl_exponential_biased.lib")
#pragma comment(lib, "absl_failure_signal_handler.lib")
#pragma comment(lib, "absl_flags.lib")
#pragma comment(lib, "absl_flags_commandlineflag.lib")
#pragma comment(lib, "absl_flags_commandlineflag_internal.lib")
#pragma comment(lib, "absl_flags_config.lib")
#pragma comment(lib, "absl_flags_internal.lib")
#pragma comment(lib, "absl_flags_marshalling.lib")
#pragma comment(lib, "absl_flags_parse.lib")
#pragma comment(lib, "absl_flags_private_handle_accessor.lib")
#pragma comment(lib, "absl_flags_program_name.lib")
#pragma comment(lib, "absl_flags_reflection.lib")
#pragma comment(lib, "absl_flags_usage.lib")
#pragma comment(lib, "absl_flags_usage_internal.lib")
#pragma comment(lib, "absl_graphcycles_internal.lib")
#pragma comment(lib, "absl_hash.lib")
#pragma comment(lib, "absl_hashtablez_sampler.lib")
#pragma comment(lib, "absl_int128.lib")
#pragma comment(lib, "absl_leak_check.lib")
#pragma comment(lib, "absl_log_severity.lib")
#pragma comment(lib, "absl_low_level_hash.lib")
#pragma comment(lib, "absl_malloc_internal.lib")
#pragma comment(lib, "absl_periodic_sampler.lib")
#pragma comment(lib, "absl_random_distributions.lib")
#pragma comment(lib, "absl_random_internal_distribution_test_util.lib")
#pragma comment(lib, "absl_random_internal_platform.lib")
#pragma comment(lib, "absl_random_internal_pool_urbg.lib")
#pragma comment(lib, "absl_random_internal_randen.lib")
#pragma comment(lib, "absl_random_internal_randen_hwaes.lib")
#pragma comment(lib, "absl_random_internal_randen_hwaes_impl.lib")
#pragma comment(lib, "absl_random_internal_randen_slow.lib")
#pragma comment(lib, "absl_random_internal_seed_material.lib")
#pragma comment(lib, "absl_random_seed_gen_exception.lib")
#pragma comment(lib, "absl_random_seed_sequences.lib")
#pragma comment(lib, "absl_raw_hash_set.lib")
#pragma comment(lib, "absl_raw_logging_internal.lib")
#pragma comment(lib, "absl_scoped_set_env.lib")
#pragma comment(lib, "absl_spinlock_wait.lib")
#pragma comment(lib, "absl_stacktrace.lib")
#pragma comment(lib, "absl_status.lib")
#pragma comment(lib, "absl_statusor.lib")
#pragma comment(lib, "absl_str_format_internal.lib")
#pragma comment(lib, "absl_strerror.lib")
#pragma comment(lib, "absl_strings.lib")
#pragma comment(lib, "absl_strings_internal.lib")
#pragma comment(lib, "absl_symbolize.lib")
#pragma comment(lib, "absl_synchronization.lib")
#pragma comment(lib, "absl_throw_delegate.lib")
#pragma comment(lib, "absl_time.lib")
#pragma comment(lib, "absl_time_zone.lib")
#pragma comment(lib, "address_sorting.lib")
#pragma comment(lib, "cares.lib")
#pragma comment(lib, "crypto.lib")
#pragma comment(lib, "gpr.lib")
#pragma comment(lib, "grpc.lib")
#pragma comment(lib, "grpc_plugin_support.lib")
#pragma comment(lib, "grpc_unsecure.lib")
#pragma comment(lib, "grpc++.lib")
#pragma comment(lib, "grpc++_alts.lib")
#pragma comment(lib, "grpc++_error_details.lib")
#pragma comment(lib, "grpc++_reflection.lib")
#pragma comment(lib, "grpc++_unsecure.lib")
#pragma comment(lib, "grpcpp_channelz.lib")
#pragma comment(lib, "re2.lib")
#pragma comment(lib, "ssl.lib")
#pragma comment(lib, "upb.lib")

#ifdef _DEBUG
#pragma comment(lib, "libprotobufd.lib")
#pragma comment(lib, "libprotobuf-lited.lib")
#pragma comment(lib, "libprotocd.lib")
//#pragma comment(lib, "zlibd.lib") // 使用zlib动态库
#pragma comment(lib, "zlibstaticd.lib")
#else
#pragma comment(lib, "libprotobuf.lib")
#pragma comment(lib, "libprotobuf-lite.lib")
#pragma comment(lib, "libprotoc.lib")
//#pragma comment(lib, "zlib.lib") // 使用zlib动态库
#pragma comment(lib, "zlibstatic.lib")
#endif

int main() {
  using namespace sa::rpc;
  using namespace sa::rpc::cli::proxy;

  auto channel =
      grpc::CreateChannel("localhost:8091", grpc::InsecureChannelCredentials());
  auto stub = Proxy::NewStub(channel);

  // 获取订阅信息
  if (1) {
    std::cout << "Call GetSubscription ...\n";
    grpc::ClientContext ctx;
    SubscriptionRsp rsp;
    auto status = stub->GetSubscription(&ctx, entity::Void{}, &rsp);
    if (status.ok()) {
      if (rsp.rsp().code() == 1) {
        auto &data = rsp.data();
        std::cout << "GetSubscription ok: " + data.DebugString() + "\n\n";
      } else {
        std::cout << "GetSubscription failed: " + rsp.rsp().msg() + "\n\n";
      }
    } else {
      std::cout << "GetSubscription failed: " + status.error_message() + "\n\n";
    }
  }

  // 添加订阅信息
  if (1) {
    std::cout << "Call AddSubscription ...\n";
    grpc::ClientContext ctx;
    entity::String rqs;
    rqs.set_value(
        "1_688001_15"); // 市场代码_证券代码_订阅类型(1|2|4|8=15, 全部)
    Rsp rsp;
    auto status = stub->AddSubscription(&ctx, rqs, &rsp);
    if (status.ok()) {
      if (rsp.code() == 1) {
        std::cout << "AddSubscription ok\n\n";
      } else {
        std::cout << "AddSubscription failed: " + rsp.msg() + "\n\n";
      }
    } else {
      std::cout << "AddSubscription failed: " + status.error_message() + "\n\n";
    }
  }

  // 取消订阅信息
  if (1) {
    std::cout << "Call DelSubscription ...\n";
    grpc::ClientContext ctx;
    entity::String rqs;
    rqs.set_value(
        "1_688001_15"); // 市场代码_证券代码_订阅类型(1|2|4|8=15, 全部)
    Rsp rsp;
    auto status = stub->DelSubscription(&ctx, rqs, &rsp);
    if (status.ok()) {
      if (rsp.code() == 1) {
        std::cout << "DelSubscription ok\n\n";
      } else {
        std::cout << "DelSubscription failed: " + rsp.msg() + "\n\n";
      }
    } else {
      std::cout << "DelSubscription failed: " + status.error_message() + "\n\n";
    }
  }

  // 读取逐笔成交
  std::thread t1([&stub]() {
    std::cout << "Start to read TickRecord ...\n";
    grpc::ClientContext ctx;
    auto reader = stub->NewTickRecordStream(&ctx, entity::Void{});
    entity::TickRecord msg;
    while (reader->Read(&msg)) {
      std::cout << "TickRecord readed: " + msg.DebugString() + "\n\n";
    }
    std::cout << "Read TickRecord done\n";
  });

  // 读取逐笔委托
  std::thread t2([&stub]() {
    std::cout << "Start to read OrderRecord ...\n";
    grpc::ClientContext ctx;
    auto reader = stub->NewOrderRecordStream(&ctx, entity::Void{});
    entity::OrderRecord msg;
    while (reader->Read(&msg)) {
      std::cout << "OrderRecord readed: " + msg.DebugString() + "\n\n";
    }
    std::cout << "Read OrderRecord done\n";
  });

  // 读取委托队列
  std::thread t3([&stub]() {
    std::cout << "Start to read OrderQueueRecord ...\n";
    grpc::ClientContext ctx;
    auto reader = stub->NewOrderQueueRecordStream(&ctx, entity::Void{});
    entity::OrderQueueRecord msg;
    while (reader->Read(&msg)) {
      std::cout << "OrderQueueRecord readed: " + msg.DebugString() + "\n\n";
    }
    std::cout << "Read OrderQueueRecord done\n";
  });

  // 读取十档行情
  std::thread t4([&stub]() {
    std::cout << "Start to read StockQuoteRecord ...\n";
    grpc::ClientContext ctx;
    auto reader = stub->NewStockQuoteRecordStream(&ctx, entity::Void{});
    entity::StockQuoteRecord msg;
    while (reader->Read(&msg)) {
      std::cout << "StockQuoteRecord readed: " + msg.DebugString() + "\n\n";
    }
    std::cout << "Read StockQuoteRecord done\n";
  });

  t1.join();
  t2.join();
  t3.join();
  t4.join();
}
