# pbinfo-discord
Trei aplicații care vor face să apară pe Discord problema la care te uiți pe pbInfo.

Scurtă descriere despre fiecare aplicație:
- pbinfo-discord-server: un server de Node.js care creează un WebSocket;
- pbinfo-discord-extension: o extensie de browser care comunică cu WebSocket-ul creat de server-ul Node.js;
- pbinfo-discord-app: aplicația care coordonează totul.


**Pentru instalare** aveți nevoie de [Node.js](https://nodejs.org/en/) (pentru server). Descărcați codul sursă de la Code -> Download ZIP.

![image](https://user-images.githubusercontent.com/68049793/179476399-34a5e0f5-d8d4-425f-81f6-51d14b8600a9.png)

Extrageți tot conținutul din fișierul ZIP într-o locație (Desktop, Documents, etc.).

1) Deschiderea aplicației - Navigați în ./pbinfo-discord-app/pbinfo-discord/ și deschideți fișierul pbinfo-discord.exe. Gata.

2) Pornirea server-ului - Navigați în ./pbinfo-discord-server/ și deschideți fișierul start_server.vbs. Gata.

3) Instalarea extensiei de browser - Mergeți pe pagina chrome://extensions de browser, activați Developer Mode și trageți folderul ./pbinfo-discord-extension (din ZIP-ul descărcat) în această pagină. Acum extensia de browser este instalată.


**Troubleshooting**:
- Server-ul trebuie pornit înainte de folosirea extensiei. Pentru a rezolva, mergeți pe pagina chrome://extensions de browser, și dați reload la extensie;
- Este posibil să trebuiască un restart la sistem după instalarea Node.js.


**Open on startup**:
Pentru a porni aplicația pbinfo-discord odată cu pornirea sistemului:
1) Navigați în folderul %APPDATA%\Roaming\Microsoft\Windows\Start Menu\Programs\Startup
2) Aici puneți shortcut la fișierele ./pbinfo-discord-app/pbinfo-discord/pbinfo-discord.exe și ./pbinfo-discord-server/start_server.vbs. Gata.

![image](https://user-images.githubusercontent.com/68049793/179478823-41a044c8-0dd2-49d5-92a4-5fa55f8b12ba.png)
