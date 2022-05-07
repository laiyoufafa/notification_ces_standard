/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_EVENT_CESFWK_SERVICES_INCLUDE_COMMON_EVENT_MANAGER_SERVICE_H
#define FOUNDATION_EVENT_CESFWK_SERVICES_INCLUDE_COMMON_EVENT_MANAGER_SERVICE_H

#include "common_event_stub.h"
#include "event_handler.h"
#include "inner_common_event_manager.h"
#include "nocopyable.h"
#include "system_ability.h"

namespace OHOS {
namespace EventFwk {
enum class ServiceRunningState { STATE_NOT_START, STATE_RUNNING };

class CommonEventManagerService : public SystemAbility, public CommonEventStub {
public:
    DECLEAR_SYSTEM_ABILITY(CommonEventManagerService);

    CommonEventManagerService();

    virtual ~CommonEventManagerService() override;

    /**
     * Publishes a common event.
     *
     * @param event Indicates the common event data.
     * @param publishInfo Indicates the publish info.
     * @param commonEventListener Indicates the common event subscriber object.
     * @param userId Indicates the user ID.
     * @return Returns true if successful; false otherwise.
     */
    virtual bool PublishCommonEvent(const CommonEventData &event, const CommonEventPublishInfo &publishinfo,
        const sptr<IRemoteObject> &commonEventListener, const int32_t &userId) override;

    /**
     * Publishes a common event.
     *
     * @param event Indicates the common event data.
     * @param publishInfo Indicates the publish info.
     * @param commonEventListener Indicates the common event subscriber.
     * @param uid Indicates the uid of application.
     * @param userId Indicates the user ID.
     * @return Returns true if successful; false otherwise.
     */
    virtual bool PublishCommonEvent(const CommonEventData &event, const CommonEventPublishInfo &publishinfo,
        const sptr<IRemoteObject> &commonEventListener, const uid_t &uid, const int32_t &userId) override;

    /**
     * Subscribes to common events.
     *
     * @param subscribeInfo Indicates the subscribe info.
     * @param commonEventListener Indicates the common event subscriber.
     * @return Returns true if successful; false otherwise.
     */
    virtual bool SubscribeCommonEvent(
        const CommonEventSubscribeInfo &subscribeInfo, const sptr<IRemoteObject> &commonEventListener) override;

    /**
     * Unsubscribes from common events.
     *
     * @param commonEventListener Indicates the common event subscriber.
     * @return Returns true if successful; false otherwise.
     */
    virtual bool UnsubscribeCommonEvent(const sptr<IRemoteObject> &commonEventListener) override;

    /**
     * Gets the current sticky common event
     *
     * @param event Indicates the common event.
     * @param eventData Indicates the common event data.
     * @return Returns true if successful; false otherwise.
     */
    virtual bool GetStickyCommonEvent(const std::string &event, CommonEventData &eventData) override;

    /**
     * Dumps state of common event service.
     *
     * @param event Specifies the information for the common event. Set null string ("") if you want to dump all.
     * @param userId Indicates the user ID.
     * @param state Indicates the state of common event service.
     * @return Returns true if successful; false otherwise.
     */
    virtual bool DumpState(const std::string &event, const int32_t &userId, std::vector<std::string> &state) override;

    /**
     * Finishes Receiver.
     *
     * @param proxy Indicates the receiver proxy.
     * @param code Indicates the code of a common event.
     * @param data Indicates the data of a common event.
     * @param abortEvent Indicates Whether to cancel the current common event.
     * @return Returns true if successful; false otherwise.
     */
    virtual bool FinishReceiver(const sptr<IRemoteObject> &proxy, const int32_t &code, const std::string &receiverData,
        const bool &abortEvent) override;

    /**
     * Freezes application.
     *
     * @param uid Indicates the uid of application.
     * @return Returns true if successful; false otherwise.
     */
    virtual bool Freeze(const uid_t &uid) override;

    /**
     * Unfreezes application.
     *
     * @param uid Indicates the Uid of application.
     * @return Returns true if successful; false otherwise.
     */
    virtual bool Unfreeze(const uid_t &uid) override;

private:
    ErrCode Init();

    // The function that overrided from SystemAbility
    virtual void OnStart() override;

    virtual void OnStop() override;

    bool IsReady() const;

    bool PublishCommonEventDetailed(const CommonEventData &event, const CommonEventPublishInfo &publishinfo,
        const sptr<IRemoteObject> &commonEventListener, const pid_t &pid, const uid_t &uid, const int32_t &userId);

private:
    std::shared_ptr<InnerCommonEventManager> innerCommonEventManager_;
    ServiceRunningState serviceRunningState_ = ServiceRunningState::STATE_NOT_START;
    std::shared_ptr<EventRunner> runner_;
    std::shared_ptr<EventHandler> handler_;

    DISALLOW_COPY_AND_MOVE(CommonEventManagerService);
};
}  // namespace EventFwk
}  // namespace OHOS

#endif  // FOUNDATION_EVENT_CESFWK_SERVICES_INCLUDE_COMMON_EVENT_MANAGER_SERVICE_H