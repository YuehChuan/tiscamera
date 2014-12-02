
#ifndef AUTOPASSFILTER_H_
#define AUTOPASSFILTER_H_

#include "tcam_algorithms.h"

#include <FilterBase.h>

#include "compiler_defines.h"

#include <vector>

VISIBILITY_INTERNAL

// forward declaration
class AutoPassFilter;

class AutoPassPropertyHandler: public PropertyImpl
{
public:

    friend class AutoPassFilter;

    AutoPassPropertyHandler ();

    bool setProperty (const Property&);

    bool getProperty (Property&);

protected:

    // device properties
    std::weak_ptr<PropertyInteger> property_exposure;
    std::weak_ptr<PropertyInteger> property_gain;
    std::weak_ptr<PropertyInteger> property_iris;

    // generated properties
    std::shared_ptr<PropertyBoolean> prop_auto_exposure;
    std::shared_ptr<PropertyBoolean> prop_auto_gain;
    std::shared_ptr<PropertyBoolean> prop_auto_iris;

    std::shared_ptr<PropertyBoolean> prop_wb;
    std::shared_ptr<PropertyBoolean> prop_auto_wb;
    std::shared_ptr<PropertyInteger> prop_wb_r;
    std::shared_ptr<PropertyInteger> prop_wb_g;
    std::shared_ptr<PropertyInteger> prop_wb_b;


};


class AutoPassFilter : public FilterBase, public std::enable_shared_from_this<AutoPassFilter>
{
public:

    AutoPassFilter ();

    void reset ();

    struct FilterDescription getDescription () const;

    bool transform (MemoryBuffer& in, MemoryBuffer& out );

    bool apply (std::shared_ptr<MemoryBuffer>);

    bool setStatus (TCAM_PIPELINE_STATUS);
    TCAM_PIPELINE_STATUS getStatus () const;

    void getVideoFormat (VideoFormat& in, VideoFormat& out) const;
    bool setVideoFormat(const VideoFormat&);
    bool setVideoFormat(const VideoFormat& in, const VideoFormat& out);

    void setDeviceProperties (std::vector<std::shared_ptr<Property>>);

    std::vector<std::shared_ptr<Property>> getFilterProperties ();

private:

    void update_params ();

    void set_gain     (int);
    void set_exposure (int);
    void set_iris     (int);

    unsigned int calculate_exposure_max ();

    static const unsigned char default_color_value = 64;

    // general
    bool valid;
    unsigned int skipped_buffer;

    int		wb_r;
    int		wb_g;
    int		wb_b;
    unsigned int exposure_max;

    FilterDescription description;
    TCAM_PIPELINE_STATUS current_status;
    tcam::VideoFormat input_format;

    tcam_auto_alg_params params;

    std::vector<unsigned char> context;
    tcam_auto_alg_context state;


    struct tcam_create_auto_alg_params init_params;

    std::shared_ptr<AutoPassPropertyHandler> handler;


};


extern "C"
{

    // FilterBase* create ();
    FB* create ();

    void close (FB*);

}

VISIBILITY_POP

#endif /* AUTOPASSFILTER_H_ */
