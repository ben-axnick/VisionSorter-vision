#pragma once

#include <boost/shared_ptr.hpp>
#include <osg/Vec3>

#include "Plugin.h"
#include "TablePlugin.h"

namespace Cube{
    const std::string CHANNEL("CUBE");
};

typedef struct cube_settings
{
    void load(const std::string &filename);

    // global
    std::string m_CubesDir; //"Data/Cube"
    double m_rotateSmoothing; //0.3 MYSTERY UNITS
    double m_translateSmoothing; //0.3
    double m_transmitRate; //0.5 SECONDS
    double m_validThreshold; //0.3 SECONDS
    // per cube
    std::string m_id;
    std::string m_arCfgPath;
    double m_cubeSize; // Physical dimensions, not just barcode 60.0mm
    osg::Vec3d m_offset; // Cube center point in relation to vehicle "center" 0., 0., 0.
} CubeSettings;


class TrackableOffsetCube
{
public:
    // NOTE: offset is cube position in relation to "ground" position
    TrackableOffsetCube(CamTracker *tracker, osg::Vec3d &offset);
    osg::Vec2d ScreenLocationCube();
    osg::Vec2d ScreenLocationBase();
    osg::Vec2d SurfaceLocation(TrackableSurface* surface);
    double GetHeading(TrackableSurface* surface);
private:
    CamTracker *m_tracker;
    osg::Vec3d m_offset;

};

class CubePlugin : public BasePlugin
{
public:
    CubePlugin(PluginManager *manager, CubeSettings cfg);
    bool Init(PluginManager *manager, const std::string &cfgFile);
    void AnnounceClients(std::vector<Plugin*> &clients);

    void IncomingFrame(osgART::GenericVideo* sourceVid, osg::Timer_t now, double elapsed);
    void IncludeInScene(osg::Node* child);

    CamTracker* CanHasTracking();

    static std::vector<boost::shared_ptr<CubePlugin> > LoadPlugins(PluginManager *manager, const std::string &cfgFile);
private:
    double m_validTime;
    osgART::Marker *m_marker;
    CamTracker *m_camTracker;
    osg::Group *m_sceneGroup;
    CubeSettings m_cfg;

    TrackableOffsetCube *m_cubeTrackable;
    TablePlugin *m_tableRef;
};

