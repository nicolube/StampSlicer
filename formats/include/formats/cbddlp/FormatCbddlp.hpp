#ifndef INCLUDE_FORMATS_FORMATCBDDLP_HPP
#define INCLUDE_FORMATS_FORMATCBDDLP_HPP

#include <stddef.h>
#include <formats/Image.hpp>
#include <formats/config/PrinterConfig.hpp>
#include <formats/config/ResinConfig.hpp>

namespace formats::cbddlp
{

	struct cbddlp_file_head_t
	{
		int magic= 0x12fd0019;
		int version = 2;
		float bed_x_mm;
		float bed_y_mm;
		float bed_z_mm;
		int zeros[2]{0, 0};
		float overall_height_mm;
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
		int projection = 0;
		int ext_config_offset;
		int ext_config_size;
		int level_set_count = 1;
		short pwm_level = 0xFF;
		short bot_pwm_level = 0xFF;
		int encryption_key = 0;
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

	struct ext2_config_t
	{
		int zeros[7]{0, 0, 0, 0, 0, 0, 0};
		u_int machine_type_offset = 0;
		int machine_type_len = 0;
		float encryption_mode = 0;
		float mysterious_id = 0;
		float antialias_level = 0;
		int software_version = 0x01060300;
		int unknown = 0x200;
		float padding1;
		float padding2;
		float padding3;
	};

	struct image_header_t
	{
		u_int size_x;
		u_int size_y;
		u_int data_offset;
		u_int data_len;
		u_int zeros[4]{0, 0, 0, 0};
	};

	struct layer_header_t
	{
		float z_mm;
		float exposure_s;
		float light_off_time_s;
		u_int data_offset;
		u_int data_len;
		u_int zeros[4]{0, 0, 0, 0};
	};

	class FormatCbddlp
	{

	public:
		void load(u_char *data, size_t length);
		static u_char *encodePreview(Image *src, u_int &length);
		static u_char *encode(Image *src, u_int &length);
		static void decode(u_char *src, u_int length, Image *dest);
		u_char *package(formats::config::PrinterConfig &printerConfig, formats::config::ResinConfig &resinConfig, Image *imageData, const int layers, size_t * size);

		// private:
		cbddlp_file_head_t header;
	};

}

#endif