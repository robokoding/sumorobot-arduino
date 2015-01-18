#ifndef CmdProcessor_h
#define CmdProcessor_h

#include "Arduino.h"

class Sumorobot;

#include "Sumorobot.h"

#define INPUT_BUFFER_LENGTH 180

typedef enum {EXPECT_ATTR, ATTR, EXPECT_VAL, VAL} parseState_t;
typedef enum {WAITING, WEBSOCKET_INIT, WEBSOCKET_RESPOND, WEBSOCKET_READY, HTTP_INIT, HTTP_RESPOND, HTTP_READY} httpState_t;
typedef enum {RAW, HTTP, WEBSOCKET} socketMode_t;

typedef void (* fp_main) (void *, char *);
typedef boolean (* fp_ready) (void *);

struct UserCmd {
  const char *cmd;
  byte type;
  fp_main fn_main;
  fp_ready fn_ready;
};

class Sumorobot;

class CmdProcessor {
  public:
    CmdProcessor();
    void addUserCmd(char* cmd, fp_main fn, fp_ready ready);
    void setup(Stream &stream, Sumorobot &sumorobot);
    void process();
  private:
    boolean processLine();
    void extractAttr(const char attr[4], char *json, char *output, char len);
    void processCmd(char &cmd, char &arg, char &id);
    void runCmd(char &cmd, char &arg, char &id);
    void sendResponse(const char state[], const char msg[], char &id);
    Stream* _stream;
    Sumorobot* _sumorobot;
    httpState_t httpState;
    socketMode_t socketMode;
    char webSocketKey[61];
    char newLineCount;
    char input_buffer[INPUT_BUFFER_LENGTH];
    byte input_buffer_pos;
    char current_id[11];
    unsigned long last_char;
    boolean processWSFrame();
    boolean processJSON();
    boolean processHeaders();
};

#endif
