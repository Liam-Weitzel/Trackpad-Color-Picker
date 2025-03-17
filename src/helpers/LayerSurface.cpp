#include "LayerSurface.hpp"

#include "Events.hpp"
#include "../hyprmag.hpp"

CLayerSurface::CLayerSurface(SMonitor* pMonitor) {
    m_pMonitor = pMonitor;

    pSurface = wl_compositor_create_surface(g_pHyprmag->m_pCompositor);

    if (!pSurface) {
        Debug::log(CRIT, "The compositor did not allow hyprmag a surface!");
        g_pHyprmag->finish(1);
        return;
    }

    pLayerSurface = zwlr_layer_shell_v1_get_layer_surface(g_pHyprmag->m_pLayerShell, pSurface, pMonitor->output, ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY, "hyprmag");

    if (!pLayerSurface) {
        Debug::log(CRIT, "The compositor did not allow hyprmag a layersurface!");
        g_pHyprmag->finish(1);
        return;
    }

    zwlr_layer_surface_v1_set_size(pLayerSurface, 0, 0);
    zwlr_layer_surface_v1_set_anchor(
        pLayerSurface, ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP | ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT | ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM | ZWLR_LAYER_SURFACE_V1_ANCHOR_LEFT);
    zwlr_layer_surface_v1_set_exclusive_zone(pLayerSurface, -1);
    zwlr_layer_surface_v1_set_keyboard_interactivity(pLayerSurface, true);
    zwlr_layer_surface_v1_add_listener(pLayerSurface, &Events::layersurfaceListener, this);
    wl_surface_commit(pSurface);

    wl_display_flush(g_pHyprmag->m_pWLDisplay);
}

CLayerSurface::~CLayerSurface() {
    // First destroy any frame callbacks
    if (frame_callback) {
        wl_callback_destroy(frame_callback);
        frame_callback = nullptr;
    }

    // Then destroy the layer surface role
    if (pLayerSurface) {
        zwlr_layer_surface_v1_destroy(pLayerSurface);
        pLayerSurface = nullptr;
    }

    // Then destroy the surface
    if (pSurface) {
        wl_surface_destroy(pSurface);
        pSurface = nullptr;
    }

    // Finally destroy buffers
    if (g_pHyprmag) {
        g_pHyprmag->destroyBuffer(&buffers[0]);
        g_pHyprmag->destroyBuffer(&buffers[1]);
        g_pHyprmag->destroyBuffer(&screenBuffer);
    }

    if (g_pHyprmag && g_pHyprmag->m_pWLDisplay) {
        wl_display_flush(g_pHyprmag->m_pWLDisplay);
    }
}
