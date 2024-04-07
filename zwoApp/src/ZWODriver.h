#include "ADDriver.h"
#include "ASICamera2.h"
#include "asynDriver.h"
#include <epicsEvent.h>

#define SHORT_WAIT (0.00025)

class ZWODriver : public ADDriver {
public:
    /**
     * \param[in] portName The name of the asyn port driver to be created.
     * \param[in] maxBuffers The maximum number of NDArray buffers that the
     *    NDArrayPool for this driver is allowed to allocate. Set this to -1 to
     *    allow an unlimited number of buffers.
     * \param[in] maxMemory The maximum amount of memory that the NDArrayPool
     * for this driver is allowed to allocate. Set this to -1 to allow an
     * unlimited amount of memory. \param[in] priority The thread priority for
     * the asyn port driver thread if ASYN_CANBLOCK is set in asynFlags.
     * \param[in] stackSize The stack size for
     *    the asyn port driver thread if ASYN_CANBLOCK is set in asynFlags.
     */
    ZWODriver(const char *portName, int maxBuffers, size_t maxMemory,
              int priority, int stackSize);
    ~ZWODriver();

    virtual asynStatus connect(asynUser *pasynUser);
    virtual asynStatus disconnect(asynUser *pasynUser);

    virtual asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
    virtual asynStatus writeFloat64(asynUser *pasynUser, epicsFloat64 value);

    void captureTask();
    void pollingTask();

private:
    int cameraID;
    ASI_CAMERA_INFO cameraInfo;

    epicsEvent *startEvent;
    epicsEvent *stopEvent;

    asynStatus connectCamera();
    asynStatus disconnectCamera();
};