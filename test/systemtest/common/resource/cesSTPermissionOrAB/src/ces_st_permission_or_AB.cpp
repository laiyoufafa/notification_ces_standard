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

#include "ces_st_permission_or_AB.h"
#include "common_event_manager.h"

namespace OHOS {
namespace AppExecFwk {
void CesSTPermissionOrAB::OnStart(const Want &want)
{
    std::string eventName = "COMMON_EVENT_DISK_REMOVED";
    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(eventName);
    EventFwk::CommonEventSubscribeInfo subscribeInfo(matchingSkills);
    auto subscriberPtr = std::make_shared<CommonEventServicesSystemTest>(subscribeInfo);
    bool resultSub = EventFwk::CommonEventManager::SubscribeCommonEvent(subscriberPtr);
    APP_LOGI("CesSTPermissionOrAB::onStart Subscribe result: %{public}d"
             "==================================================================================="
             "================== ",
        resultSub);
    GetWantInfo(want);
    Ability::OnStart(want);
}

void CesSTPermissionOrAB::OnNewWant(const Want &want)
{
    GetWantInfo(want);
    Ability::OnNewWant(want);
}

void CesSTPermissionOrAB::OnForeground(const Want &want)
{
    GetWantInfo(want);
    Ability::OnForeground(want);
}

void CesSTPermissionOrAB::OnStop()
{
    Ability::OnStop();
}

void CesSTPermissionOrAB::OnActive()
{
    Ability::OnActive();
    if (std::string::npos != shouldReturn.find(GetAbilityName())) {
        TerminateAbility();
    }
    Clear();
}

void CesSTPermissionOrAB::OnInactive()
{
    Ability::OnInactive();
}

void CesSTPermissionOrAB::OnBackground()
{
    Ability::OnBackground();
}

void CesSTPermissionOrAB::Clear()
{
    shouldReturn = "";
    targetBundle = "";
    targetAbility = "";
}

void CesSTPermissionOrAB::GetWantInfo(const Want &want)
{
    Want mWant(want);
    shouldReturn = mWant.GetStringParam("shouldReturn");
    targetBundle = mWant.GetStringParam("targetBundle");
    targetAbility = mWant.GetStringParam("targetAbility");
}

REGISTER_AA(CesSTPermissionOrAB)
}  // namespace AppExecFwk
}  // namespace OHOS