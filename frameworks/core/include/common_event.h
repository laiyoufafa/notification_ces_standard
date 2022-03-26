/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_EVENT_CESFWK_INNERKITS_INCLUDE_COMMON_EVENT_H
#define FOUNDATION_EVENT_CESFWK_INNERKITS_INCLUDE_COMMON_EVENT_H

#include <map>
#include <mutex>

#include "common_event_listener.h"
#include "icommon_event.h"

namespace OHOS {
namespace EventFwk {
class CommonEvent {
public:
    /**
     * Publish an ordered, sticky, or standard common event.
     *
     * @param data the common event data
     * @param publishInfo the publish info
     * @param subscriber the common event subscriber
     */
    bool PublishCommonEvent(const CommonEventData &data, const CommonEventPublishInfo &publishInfo,
        const std::shared_ptr<CommonEventSubscriber> &subscriber);

    /**
     * Publish an ordered, sticky, or standard common event.
     *
     * @param data the common event data
     * @param publishInfo the publish info
     * @param subscriber the common event subscriber
     * @param userId indicates the user ID
     */
    bool PublishCommonEventAsUser(const CommonEventData &data, const CommonEventPublishInfo &publishInfo,
        const std::shared_ptr<CommonEventSubscriber> &subscriber, const int32_t &userId);

    /**
     * Publish an ordered, sticky, or standard common event.
     *
     * @param data the common event data
     * @param publishInfo the publish info
     * @param subscriber the common event subscriber
     * @param uid Uid of application.
     */
    bool PublishCommonEvent(const CommonEventData &data, const CommonEventPublishInfo &publishInfo,
        const std::shared_ptr<CommonEventSubscriber> &subscriber, const uid_t &uid);

    /**
     * Publish an ordered, sticky, or standard common event.
     *
     * @param data the common event data
     * @param publishInfo the publish info
     * @param subscriber the common event subscriber
     * @param uid Uid of application.
     * @param userId Indicates the user ID
     */
    bool PublishCommonEventAsUser(const CommonEventData &data, const CommonEventPublishInfo &publishInfo,
        const std::shared_ptr<CommonEventSubscriber> &subscriber, const uid_t &uid,
        const int32_t &userId);

    /**
     * Subscribe to common events.
     *
     * @param subscriber the common event subscriber
     */
    bool SubscribeCommonEvent(const std::shared_ptr<CommonEventSubscriber> &subscriber);

    /**
     * Unsubscribe from common events.
     *
     * @param subscriber the common event subscriber
     */
    bool UnSubscribeCommonEvent(const std::shared_ptr<CommonEventSubscriber> &subscriber);

    /**
     * Gets the current sticky common event
     *
     * @param event the common event
     * @param eventData the common event data
     */
    bool GetStickyCommonEvent(const std::string &event, CommonEventData &eventData);

    /**
     * Finish Receiver.
     *
     * @param proxy Receiver proxy.
     * @param code the code of a common event.
     * @param data the data of a common event.
     * @param abortEvent Cancel the current common event.
     * @return Finish Receiver success or not.
     */
    bool FinishReceiver(
        const sptr<IRemoteObject> &proxy, const int &code, const std::string &data, const bool &abortEvent);

    /**
     * Dump state of common event service.
     *
     * @param event Specifies the information for the common event. Set null string ("") if you want to dump all.
     * @param userId indicates the user ID
     * @param state the state of common event service
     */
    bool DumpState(const std::string &event, const int32_t &userId, std::vector<std::string> &state);

    /**
     * Reset Common Event Proxy.
     */
    void ResetCommonEventProxy();

    /**
     * Freeze application.
     *
     * @param uid Uid of application.
     */
    bool Freeze(const uid_t &uid);

    /**
     * Unfreeze application.
     *
     * @param uid Uid of application.
     */
    bool Unfreeze(const uid_t &uid);

private:
    /**
     * Get common event proxy.
     *
     * @return Get common event proxy success or not
     */
    bool GetCommonEventProxy();

    /**
     * Get common evenet listener.
     *
     * @param  subscriber the subscriber
     * @param  commonEventListener  the common event listener
     * @return Get common event listener success or not
     */
    uint8_t CreateCommonEventListener(
        const std::shared_ptr<CommonEventSubscriber> &subscriber, sptr<IRemoteObject> &commonEventListener);

    /**
     * Parameter checking for publishing public events
     *
     * @param data the common event data
     * @param publishInfo the publish info
     * @param subscriber the common event subscriber
     */
    bool PublishParameterCheck(const CommonEventData &data, const CommonEventPublishInfo &publishInfo,
        const std::shared_ptr<CommonEventSubscriber> &subscriber, sptr<IRemoteObject> &commonEventListener);

private:
    bool isProxyValid_ = false;
    std::mutex mutex_;
    std::mutex eventListenersMutex_;
    sptr<ICommonEvent> commonEventProxy_;
    std::map<std::shared_ptr<CommonEventSubscriber>, sptr<CommonEventListener>> eventListeners_;
    sptr<IRemoteObject::DeathRecipient> recipient_;
    const unsigned int SUBSCRIBER_MAX_SIZE = 200;
    static const uint8_t ALREADY_SUBSCRIBED = 0;
    static const uint8_t INITIAL_SUBSCRIPTION = 1;
    static const uint8_t SUBSCRIBE_FAILED = 2;
};
}  // namespace EventFwk
}  // namespace OHOS

#endif  // FOUNDATION_EVENT_CESFWK_INNERKITS_INCLUDE_COMMON_EVENT_H