#ifndef INCLUDE_FORMATS_FORMATCBDDLP_HPP
#define INCLUDE_FORMATS_FORMATCBDDLP_HPP

#include <stddef.h>

namespace formats::cbddlp {
    
    struct cbddlp_file_head_t
		{
			int magic;
			int version;
			float bed_x_mm;
			float bed_y_mm;
			float bed_z_mm;
			int : 32;
			int : 32;
			int : 32;
			float layer_height_mm;
			float exposure_s;
			float bot_exposure_s;
			float light_off_time_s;
			int bot_layer_count;
			int resolution_x;
			int resolution_y;
			int large_preview_offset;
			int layer_table_offset;
			int layer_table_count;
			int small_preview_offset;
			int print_time_s;
			int projection;
			int ext_config_offset;
			int ext_config_size;
			int level_set_count;
			short pwm_level;
			short bot_pwm_level;
			int encryption_key;
			int ext_config2_offset;
			int ext_config2_size;
		};

		struct ext_config_t
		{
			float bot_lift_dist_mm;
			float bot_lift_speed_mmpm;
			float lift_dist_mm;
			float lift_speed_mmpm;
			float retract_speed_mmpm;
			float resin_volume_ml;
			float resin_mass_g;
			float resin_cost;
			float bot_light_off_time_s;
			float light_off_time_s;
			int bot_layer_count;
			float padding1;
			float padding2;
			float padding3;
			float padding4;
		};

		struct layer_definition_t
		{
			float layerPositionZ;
			float layerExposure;
			float layerOffTimeSeconds;
			int dataAddress;
			int dataSize;
			int unknown1;
			int unknown2;
			int unknown3;
			int unknown4;
		};

        struct image_header_t {
            int size_x;
            int size_y;
            int data_offset;
            int data_len;
        };

        struct layer_header_t {
            int z_mm;
            int exposure_s;
            int light_off_time_s;
            int data_offset;
            int data_len;
        };

        class FormatCbddlp {

            public:
            void load(char *data, size_t length);

            //private:
            cbddlp_file_head_t header;
        };

}

#endif