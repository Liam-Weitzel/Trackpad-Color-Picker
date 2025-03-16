#pragma once

#include "defines.hpp"
#include "helpers/LayerSurface.hpp"
#include "helpers/PoolBuffer.hpp"

#include <libinput.h>

struct GestureState {
    bool active = false;
    float initial_scale = 1.0f;
    float current_scale = 1.0f;
    uint32_t finger_count = 0;
};

struct ScalePair {
    float monitor_scale;
    float target_scale;
};

// Ordered by monitor_scale
const std::vector<ScalePair> SCALE_MAP = {
    {0.5f, 2.0f},
    {0.6f, 1.66f},
    {0.7f, 1.41f},
    {0.9f, 1.1f},
    {1.1f, 1.8f},
    {1.2f, 1.6f},
    {1.3f, 1.55f},
    {1.5f, 1.32f},
    {1.7f, 1.2f},
    {2.1f, 1.44f},
    {2.8f, 1.0f}
};


class CHyprmag {
  public:
    void                                        init();

    struct wp_fractional_scale_manager_v1* m_pFractionalScaleMgr = nullptr;
    std::mutex                                  m_mtTickMutex;
    zxdg_output_manager_v1* m_pXDGOutputMgr = nullptr;

    wl_compositor*                              m_pCompositor        = nullptr;
    wl_display*                                 m_pWLDisplay         = nullptr;
    wl_registry*                                m_pWLRegistry        = nullptr;
    wl_shm*                                     m_pWLSHM             = nullptr;
    zwlr_layer_shell_v1*                        m_pLayerShell        = nullptr;
    zwlr_screencopy_manager_v1*                 m_pSCMgr             = nullptr;
    wp_cursor_shape_manager_v1*                 m_pCursorShape       = nullptr;
    wp_cursor_shape_device_v1*                  m_pCursorShapeDevice = nullptr;

    xkb_context*                                m_pXKBContext = nullptr;
    xkb_keymap*                                 m_pXKBKeymap  = nullptr;
    xkb_state*                                  m_pXKBState   = nullptr;

    bool                                        m_bRenderInactive = false;
    int                                         m_iRadius         = 200;
    float                                       m_fScale          = 4.0f;

    bool                                        m_bRunning = true;

    std::vector<std::unique_ptr<SMonitor>>      m_vMonitors;
    std::vector<std::unique_ptr<CLayerSurface>> m_vLayerSurfaces;

    void                                        createSeat(wl_seat*);

    CLayerSurface*                              m_pLastSurface;

    Vector2D                                    m_vLastCoords;

    void                                        renderSurface(CLayerSurface*, bool forceInactive = false);

    void                                        createBuffer(SPoolBuffer*, int32_t, int32_t, uint32_t, uint32_t);
    void                                        destroyBuffer(SPoolBuffer*);
    int                                         createPoolFile(size_t, std::string&);
    bool                                        setCloexec(const int&);
    void                                        recheckACK();

    void                                        sendFrame(CLayerSurface*);

    SPoolBuffer*                                getBufferForLS(CLayerSurface*);

    void                                        convertBuffer(SPoolBuffer*);
    void*                                       convert24To32Buffer(SPoolBuffer*);

    void                                        markDirty();

    void                                        finish(int code = 0);

    struct libinput* m_pLibinput = nullptr;
    struct libinput_device* m_pLibinputDevice = nullptr;
    GestureState m_gestureState;

    // Add new methods for gesture handling
    void handlePinchBegin(struct libinput_event_gesture* event);
    float getTargetScale(float monitor_scale);
    void handlePinchUpdate(struct libinput_event_gesture* event);
    void handlePinchEnd(struct libinput_event_gesture* event);
    void processLibinputEvents();
  private:
};

inline std::unique_ptr<CHyprmag> g_pHyprmag;
