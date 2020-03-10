
class MediaControl {
public:

    enum State {
        STATE_ERROR = -1,
        STATE_IDLE = 0,
        STATE_INIT = 1,
        STATE_RUN = 2,
    };
    MediaControl();
    ~MediaControl();

    virtual int init() = 0;
    virtual int uninit() = 0;
    virtual int start(int num, int interval, std::function<void(int result, int seq_num)> cb) = 0;
    virtual int start() = 0;
    virtual int stop() = 0;
    virtual int getState() = 0;

    virtual std::string getURI() = 0;
    virtual setURI(std::string uri) = 0;

    virtual int setResolution(Resolution res) = 0;
    virtual int getResolution(Resolution * res) = 0;

    virtual int do(Command * command ) = 0;

private:
    Resolution res;
    CommandParser commandParser;

};
