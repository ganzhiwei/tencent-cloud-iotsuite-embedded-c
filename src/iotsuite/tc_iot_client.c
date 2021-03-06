#ifdef __cplusplus
extern "C" {
#endif

#include "tc_iot_inc.h"

int tc_iot_mqtt_client_construct(tc_iot_mqtt_client* c,
                                 tc_iot_mqtt_client_config* p_client_config) {
    IF_NULL_RETURN(c, TC_IOT_NULL_POINTER);
    IF_NULL_RETURN(p_client_config, TC_IOT_NULL_POINTER);

    tc_iot_mqtt_init(c, p_client_config);

    MQTTPacket_connectData default_data = MQTTPacket_connectData_initializer;

    c->connect_options = default_data;
    MQTTPacket_connectData* data = &(c->connect_options);
    data->willFlag = 0;
    data->MQTTVersion = 4;
    data->clientID.cstring = p_client_config->device_info.client_id;
    data->username.cstring = p_client_config->device_info.username;
    data->password.cstring = p_client_config->device_info.password;
    data->keepAliveInterval = p_client_config->keep_alive_interval;
    data->cleansession = p_client_config->clean_session;

    int rc = tc_iot_mqtt_connect(c, data);
    if (TC_IOT_SUCCESS == rc) {
        LOG_TRACE("mqtt client connect %s:%d success", p_client_config->host,
                  p_client_config->port);
    } else {
        LOG_ERROR("!!! mqtt cllient connect %s:%d failed retcode %d",
                  p_client_config->host, p_client_config->port, rc);
    }
    return TC_IOT_SUCCESS;
}

void tc_iot_mqtt_client_destroy(tc_iot_mqtt_client* c) {}

char tc_iot_mqtt_client_is_connected(tc_iot_mqtt_client* c) {
    IF_NULL_RETURN(c, TC_IOT_NULL_POINTER);
    return tc_iot_mqtt_is_connected(c);
}

int tc_iot_mqtt_client_yield(tc_iot_mqtt_client* c, int timeout_ms) {
    IF_NULL_RETURN(c, TC_IOT_NULL_POINTER);
    tc_iot_mqtt_yield(c, timeout_ms);
}

int tc_iot_mqtt_client_publish(tc_iot_mqtt_client* c, const char* topic,
                               tc_iot_mqtt_message* msg) {
    IF_NULL_RETURN(c, TC_IOT_NULL_POINTER);
    IF_NULL_RETURN(topic, TC_IOT_NULL_POINTER);
    return tc_iot_mqtt_publish(c, topic, msg);
}

int tc_iot_mqtt_client_subscribe(tc_iot_mqtt_client* c,
                                 const char* topic_filter,
                                 tc_iot_mqtt_qos_e qos,
                                 message_handler msg_handler) {
    IF_NULL_RETURN(c, TC_IOT_NULL_POINTER);
    IF_NULL_RETURN(topic_filter, TC_IOT_NULL_POINTER);
    return tc_iot_mqtt_subscribe(c, topic_filter, qos, msg_handler);
}

int tc_iot_mqtt_client_unsubscribe(tc_iot_mqtt_client* c,
                                   const char* topic_filter) {
    IF_NULL_RETURN(c, TC_IOT_NULL_POINTER);
    IF_NULL_RETURN(topic_filter, TC_IOT_NULL_POINTER);
    return tc_iot_mqtt_unsubscribe(c, topic_filter);
}

int tc_iot_mqtt_client_disconnect(tc_iot_mqtt_client* c) {
    IF_NULL_RETURN(c, TC_IOT_NULL_POINTER);
    return tc_iot_mqtt_disconnect(c);
}

#ifdef __cplusplus
}
#endif
