const ws = new WebSocket('ws://localhost:3000')

ws.onopen = () => {
   console.log(`Connected to the WebSocket server.`)
}

ws.onclose = () => {
   console.log(`Disconnected from the WebSocket server.`)
}

let lastPath = ''

setInterval(() => {
   chrome.tabs.query( {active: true} )
      .then((tabs) => {
         if (tabs[0].status !== 'complete')
            return

         const url = new URL(tabs[0].url)
         if (lastPath !== url.pathname)
         {
            if (!(url.hostname.endsWith('.pbinfo.ro') && !url.hostname.endsWith('/pbinfo.ro')))
               ws.send(JSON.stringify({path: ' ', title: ''}))
            else
               ws.send(JSON.stringify({path: url.pathname, title: tabs[0].title}))
            lastPath = url.pathname
         }
      })
}, 500);



/// keep the extension active forever
let lifeline;

keepAlive();

chrome.runtime.onConnect.addListener(port => {
   if (port.name === 'keepAlive') {
      lifeline = port;
      setTimeout(keepAliveForced, 295e3); // 5 minutes minus 5 seconds
      port.onDisconnect.addListener(keepAliveForced);
   }
});

function keepAliveForced() {
   lifeline?.disconnect();
   lifeline = null;
   keepAlive();
}

async function keepAlive() {
   if (lifeline) return;
   for (const tab of await chrome.tabs.query({ url: '*://*/*' })) {
      try {
         await chrome.scripting.executeScript({
            target: { tabId: tab.id },
            function: () => chrome.runtime.connect({ name: 'keepAlive' }),
            // `function` will become `func` in Chrome 93+
         });
         chrome.tabs.onUpdated.removeListener(retryOnTabUpdate);
         return;
      } catch (e) {}
   }
   chrome.tabs.onUpdated.addListener(retryOnTabUpdate);
}

async function retryOnTabUpdate(tabId, info, tab) {
  if (info.url && /^(file|https?):/.test(info.url)) {
    keepAlive();
  }
}