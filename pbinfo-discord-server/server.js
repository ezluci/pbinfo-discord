const fs = require('fs')
const http = require('http')
const WebSocketServer = require('websocket').server
const PORT = 3000

const defaultPage = fs.readFileSync('index.html', 'utf8')

const server = http.createServer((req, res) => {
   res.end(defaultPage)
})

server.listen(PORT, () => {
   console.log(`The server works on port ${PORT}.`)
})

const wsServer = new WebSocketServer( {httpServer: server} )

wsServer.on('request', (req) => {

   const connection = req.accept(null, req.origin)
   console.log(`New connection.`)

   connection.on('message', (msg) => {
      const tab = JSON.parse(msg.utf8Data)
      fs.writeFileSync('../current-tab.txt', `${tab.path}\n${tab.title}`)
      console.log(`Received a tab update: {path: "${tab.path}", title: "${tab.title}"}.`)
   })

   connection.on('close', () => {
      console.log(`Connection closed.`)
   })
})