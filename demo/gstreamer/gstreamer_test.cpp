#include <gst/gst.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char *argv[]) {
    GstElement *pipeline, *source, *capsfilter, *decoder, *convert, *sink;
    GstBus *bus;
    GstMessage *msg;
    GstSample *sample;
    GstMapInfo map;
    gboolean terminate = FALSE;
    GstCaps *caps;

    gst_init(&argc, &argv);

    // 创建GStreamer管道
    pipeline = gst_pipeline_new("usb-camera-pipeline");
    source = gst_element_factory_make("v4l2src", "source");
    capsfilter = gst_element_factory_make("capsfilter", "capsfilter");
    decoder = gst_element_factory_make("jpegdec", "decoder");
    convert = gst_element_factory_make("videoconvert", "convert");
    sink = gst_element_factory_make("appsink", "sink");

    if (!pipeline || !source || !capsfilter || !decoder || !convert || !sink) {
        g_printerr("Failed to create elements\n");
        return -1;
    }

    // 设置摄像头设备
    g_object_set(G_OBJECT(source), "device", "/dev/video0", NULL);

    // 设置视频格式
    caps = gst_caps_new_simple("image/jpeg",
                               "framerate", GST_TYPE_FRACTION, 30, 1,
                               NULL);
    g_object_set(G_OBJECT(capsfilter), "caps", caps, NULL);
    gst_caps_unref(caps);

    // 设置appsink属性
    g_object_set(G_OBJECT(sink), "emit-signals", TRUE, "sync", FALSE, NULL);

    // 添加元素到管道并链接
    gst_bin_add_many(GST_BIN(pipeline), source, capsfilter, decoder, convert, sink, NULL);
    if (!gst_element_link_many(source, capsfilter, decoder, convert, sink, NULL)) {
        g_printerr("Elements could not be linked\n");
        gst_object_unref(pipeline);
        return -1;
    }

    // 创建OpenCV视频写入器
    VideoWriter writer("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(640, 480));

    if (!writer.isOpened()) {
        g_printerr("Could not open the output video file for write\n");
        return -1;
    }

    // 开始播放
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // 获取总线并监听消息
    bus = gst_element_get_bus(pipeline);
    while (!terminate) {
        // 获取appsink样本
        g_signal_emit_by_name(sink, "pull-sample", &sample);

        if (sample) {
            // 获取样本中的缓冲区数据
            GstBuffer *buffer = gst_sample_get_buffer(sample);
            gst_buffer_map(buffer, &map, GST_MAP_READ);

            // 转换为OpenCV Mat
            Mat frame(Size(640, 480), CV_8UC3, (char*)map.data);
            printf("one frame\n");

            // 写入视频文件
            writer.write(frame);

            // 解锁缓冲区
            gst_buffer_unmap(buffer, &map);
            gst_sample_unref(sample);
        } else {
            // 如果没有样本，检查消息
            msg = gst_bus_timed_pop_filtered(bus, 100 * GST_MSECOND, (GstMessageType) (GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

            if (msg != NULL) {
                if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR) {
                    GError *err;
                    gchar *debug_info;

                    gst_message_parse_error(msg, &err, &debug_info);
                    g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
                    g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
                    g_clear_error(&err);
                    g_free(debug_info);
                    terminate = TRUE;
                } else if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_EOS) {
                    g_print("End-Of-Stream reached.\n");
                    terminate = TRUE;
                }
                gst_message_unref(msg);
            }
        }
    }

    // 清理
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    writer.release();

    return 0;
}
