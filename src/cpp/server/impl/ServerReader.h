// Author: Jin Qing (http://blog.csdn.net/jq0123)
#ifndef SERVER_SERVER_READER_H
#define SERVER_SERVER_READER_H

#include <grpc_cb_core/server/server_reader.h>  // for grpc_cb_core::ServerReader

#include "common/LuaRefFwd.h"  // forward LuaRef

#include <string>

namespace grpc_cb_core {
class Status;
}  // namespace grpc_cb_core

namespace impl {

struct LuaReaderFunctions;

// ServerReader is the interface of client streaming handler,
//  for both client-side streaming and bi-directional streaming.
// Thread-safe.
class ServerReader : public grpc_cb_core::ServerReader {
 public:
  explicit ServerReader(const LuaIntf::LuaRef& luaReader);
  virtual ~ServerReader();

 public:
  void OnMsgStr(const std::string& msg_str) override;
  void OnError(const grpc_cb_core::Status& status) override;
  void OnEnd() override;

 private:
  void InitLuaReaderFunctions(const LuaIntf::LuaRef& luaReader);

 private:
  std::unique_ptr<LuaReaderFunctions> m_pLuaReaderFunctions;
};  // class ServerReader

}  // namespace impl
#endif  // SERVER_SERVER_READER_H
