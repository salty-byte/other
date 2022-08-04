# gRPC tips

## Quick start: Web

- link: https://grpc.io/docs/platforms/web/quickstart/

```bash
$ git clone https://github.com/grpc/grpc-web
$ cd grpc-web
$ docker-compose pull prereqs node-server envoy commonjs-client
$ docker-compose up -d node-server envoy commonjs-client
```

- 疎通確認: http://localhost:8081/echotest.html

```bash
# shutdown
$ docker-compose down
```

## grpcurl

- https://github.com/fullstorydev/grpcurl
- protoファイルを用いて、curlコマンドのようにリクエストを送信できる。
- 流れとしては以下のような感じ。
    - リクエスト： JSONテキスト => (protobufバイナリに変換) => サーバ
    - レスポンス： サーバ => (protobufバイナリのデコード) => JSONテキスト

### インストール: go

```bash
$ go install github.com/fullstorydev/grpcurl/cmd/grpcurl@latest
```

### 利用方法

- gRPCサーバーでreflection機能を有効になっている場合、protoファイルは不要。
    - 具体的には、import-pathやprotoオプションが不要。
- httpでテストする場合は、plaintextオプションが必要。
- 参考：https://kiririmode.hatenablog.jp/entry/20181008/1538984412

#### protoファイルで定義されているサービス一覧の取得

```bash
$ grpcurl -plaintext -import-path ./echo -proto echo.proto localhost:8080 list
# => grpc.gateway.testing.EchoService
```

#### サービスの詳細の取得

```bash
$ grpcurl -plaintext -import-path ./grpc-web/grpc-web/net/grpc/gateway/examples/echo -proto echo.proto localhost:8080 describe grpc.gateway.testing.EchoService
# => grpc.gateway.testing.EchoService is a service:
# // A simple echo service.
# service EchoService {
#   // A sequence of requests followed by one response (streamed upload).
#   // The server returns the total number of messages as the result.
#   rpc ClientStreamingEcho ( stream .grpc.gateway.testing.ClientStreamingEchoRequest ) returns ( .grpc.gateway.testing.ClientStreamingEchoResponse );
#   // One request followed by one response
#   // The server returns the client message as-is.
#   rpc Echo ( .grpc.gateway.testing.EchoRequest ) returns ( .grpc.gateway.testing.EchoResponse );
#   // Sends back abort status.
#   rpc EchoAbort ( .grpc.gateway.testing.EchoRequest ) returns ( .grpc.gateway.testing.EchoResponse );
#   // A sequence of requests with each message echoed by the server immediately.
#   // The server returns the same client messages in order.
#   // E.g. this is how the speech API works.
#   rpc FullDuplexEcho ( stream .grpc.gateway.testing.EchoRequest ) returns ( stream .grpc.gateway.testing.EchoResponse );
#   // A sequence of requests followed by a sequence of responses.
#   // The server buffers all the client messages and then returns the same
#   // client messages one by one after the client half-closes the stream.
#   // This is how an image recognition API may work.
#   rpc HalfDuplexEcho ( stream .grpc.gateway.testing.EchoRequest ) returns ( stream .grpc.gateway.testing.EchoResponse );
#   // One empty request, ZERO processing, followed by one empty response
#   // (minimum effort to do message serialization).
#   rpc NoOp ( .grpc.gateway.testing.Empty ) returns ( .grpc.gateway.testing.Empty );
#   // One request followed by a sequence of responses (streamed download).
#   // The server will return the same client message repeatedly.
#   rpc ServerStreamingEcho ( .grpc.gateway.testing.ServerStreamingEchoRequest ) returns ( stream .grpc.gateway.testing.ServerStreamingEchoResponse );
#   // One request followed by a sequence of responses (streamed download).
#   // The server abort directly.
#   rpc ServerStreamingEchoAbort ( .grpc.gateway.testing.ServerStreamingEchoRequest ) returns ( stream .grpc.gateway.testing.ServerStreamingEchoResponse );
# }
```

#### メッセージ送信

```bash
$ grpcurl -plaintext -d '{"message":"test"}' -import-path ./echo -proto echo.proto localhost:8080 grpc.gateway.testing.EchoService/Echo
# => {
#   "message": "test"
# }
```
