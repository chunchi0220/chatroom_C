常用的 socket 有兩種，SOCK_STREAM( for TCP )、SOCK_DGRAM( for UDP )，這次的實作是使用 TCP 的 socket 來做一個簡單的聊天室

Server主要功能
在特定的 port 上進行監聽，等待 client 端連線
使用者可以配置 server 端的監聽 port
向連接的 client 發送登入成功的消息
向已經連接到 server 的 client 端使用者發送系統消息
Client主要功能
運行 client 端連接到已經開啟服務的 server 端
使用者可以向 server 發送消息
使用者可以接受 server 發送的系統消息
