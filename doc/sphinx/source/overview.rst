Overview
========
A short overview over the different classes and their functions.

main
    Startup

MainWindow
    Responsible for drawing the main window and its contents. Responsible for updating GUI. Communicates with a MessageHandler instance

MessageHandler
    Parses and generates JSON for the communication over the websocket. Communicates between MainWindow (GUI) and WebSocketClientQt
    (websocket implementation)

WebSocketClientQt
    Communicates with the Mopidy WebSocket (sends and receives messages). Derived from QWebSocket class.

models/Track
    Track model contains information about a track (title, length, author etc.)

models/Playlist
    Playlist model contains tracks and is used in the MainWindow to populate a table with the current playlist.


WebSocket
---------
Communication with the Mopidy websocket takes place in the WebSocketClientQt class. Received events from Mopidy get parsed
and the respective objects get updated. The MessageHandler is higher level than the WebSocketClientQt class since he prepares
parses messages while the WebSocketClientQt class simply sends and receives messages.

An example:
WebSocketClientQt receives a message with the event "tracklist_changed". This event then gets handled from MessageHandler who
itself creates a message to request the current playlist. This message gets sent to Mopidy by the WebSocketClientQt. The answer
to the playlist request gets again handled by the MessageHandler. In case the request was successfull the MessageHandler creates
Track models and sends them to the MainWindow to be displayed on the GUI.
