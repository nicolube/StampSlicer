#include <iostream>
#include <fstream>
#include <formats/cbddlp/FormatCbddlp.hpp>

using namespace std;

void printHelp(const char *cmd)
{
    cout << "Syntax: " << cmd << " <format> <file>" << endl
         << "Formats:" << endl
         << "cbddlp" << endl;
}

namespace formats::cbddlp
{
    void printCbddlp(unsigned char *data)
    {
        cbddlp_file_head_t header;
        ext_config_t ext1;
        ext2_config_t ext2;
        memcpy(&header, data, sizeof(cbddlp_file_head_t));
        memcpy(&ext1, data + header.ext_config_offset, sizeof(ext_config_t));
        memcpy(&ext2, data + header.ext_config2_offset, sizeof(ext2_config_t));
        string machine_type((char*)(data + ext2.machine_type_offset), ext2.machine_type_len);

        cout << "Content of cbddlp:" << endl
             << "==================" << endl
             << endl
             << "Header: " << endl
             << "--------" << endl
             << "magic: " << header.magic << endl
             << "version: " << header.version << endl
             << "bed_x_mm: " << header.bed_x_mm << endl
             << "bed_y_mm: " << header.bed_y_mm << endl
             << "bed_z_mm: " << header.bed_z_mm << endl
             << "overall_height_mm: " << header.overall_height_mm << endl
             << "layer_height_mm: " << header.layer_height_mm << endl
             << "exposure_s: " << header.exposure_s << endl
             << "bot_exposure_s: " << header.bot_exposure_s << endl
             << "light_off_time_s: " << header.light_off_time_s << endl
             << "bot_layer_count: " << header.bot_layer_count << endl
             << "resolution_x: " << header.resolution_x << endl
             << "resolution_y: " << header.resolution_y << endl
             << "large_preview_offset: " << header.large_preview_offset << endl
             << "small_preview_offset: " << header.small_preview_offset << endl
             << "layer_table_offset: " << header.layer_table_offset << endl
             << "layer_table_count: " << header.layer_table_count << endl
             << "print_time_s: " << header.print_time_s << endl
             << "projection: " << header.projection << endl
             << "ext_config_offset: " << header.ext_config_offset << endl
             << "ext_config_size: " << header.ext_config_size << endl
             << "level_set_count: " << header.level_set_count << endl
             << "pwm_level: " << header.pwm_level << endl
             << "bot_pwm_level: " << header.bot_pwm_level << endl
             << "encryption_key: " << header.encryption_key << endl
             << "ext_config2_offset: " << header.ext_config2_offset << endl
             << "ext_config2_size: " << header.ext_config2_size << endl
             << endl
             << "Ext config: " << endl
             << "-----------" << endl
             << "bot_lift_dist_mm: " << ext1.bot_lift_dist_mm << endl
             << "bot_lift_speed_mmpm: " << ext1.bot_lift_speed_mmpm << endl
             << "lift_dist_mm: " << ext1.lift_dist_mm << endl
             << "lift_speed_mmpm: " << ext1.lift_speed_mmpm << endl
             << "retract_speed_mmpm: " << ext1.retract_speed_mmpm << endl
             << "resin_volume_ml: " << ext1.resin_volume_ml << endl
             << "resin_mass_g: " << ext1.resin_mass_g << endl
             << "resin_cost: " << ext1.resin_cost << endl
             << "bot_light_off_time_s: " << ext1.bot_light_off_time_s << endl
             << "light_off_time_s: " << ext1.light_off_time_s << endl
             << "bot_layer_count: " << ext1.bot_layer_count << endl
             << "padding1: " << ext1.padding1 << endl
             << "padding2: " << ext1.padding2 << endl
             << "padding3: " << ext1.padding3 << endl
             << endl
             << "Ext config2: " << endl
             << "------------" << endl
             << "machine_type_offset: " << ext2.machine_type_offset << endl
             << "machine_type_len: " << ext2.machine_type_len << endl
             << "encryption_mode: " << ext2.encryption_mode << endl
             << "mysterious_id: " << ext2.mysterious_id << endl
             << "antialias_level: " << ext2.antialias_level << endl
             << "software_version: " << ext2.software_version << endl
             << "unknown: " << ext2.unknown << endl
             << "padding1: " << ext2.padding1 << endl
             << "padding2: " << ext2.padding2 << endl
             << "padding3: " << ext2.padding3 << endl
             << endl
             << "Machine Type: " << endl
             << "-------------" << endl
             << "machine_type: " << machine_type << endl;
    }
}

int main(int argc, const char **argv)
{
    if (argc != 3)
    {
        printHelp(argv[0]);
        return 1;
    }

    string type = argv[1];
    string file = argv[2];
    ifstream inputFile;
    inputFile.open(file);
    if (!inputFile.good())
    {
        cout << "File not found: " << file << endl;
        return 2;
    }

    // Load file
    inputFile.seekg(0, ios::end);
    streampos end = inputFile.tellg();
    inputFile.seekg(0, ios::beg);
    streampos start = inputFile.tellg();
    size_t size = end - start;
    unsigned char *fileData = new unsigned char[size];
    inputFile.read((char *)fileData, size);
    inputFile.close();

    if (type.compare("cbddlp") == 0)
    {
        formats::cbddlp::printCbddlp(fileData);
        return 0;
    } else {
        printHelp(argv[0]);
    }
    return 0;
}
