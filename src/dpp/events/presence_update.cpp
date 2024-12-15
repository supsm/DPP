/************************************************************************************
 *
 * D++, A Lightweight C++ library for Discord
 *
 * SPDX-License-Identifier: Apache-2.0
 * Copyright 2021 Craig Edwards and D++ contributors 
 * (https://github.com/brainboxdotcc/DPP/graphs/contributors)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ************************************************************************************/
#include <dpp/discordevents.h>
#include <dpp/cluster.h>
#include <dpp/stringops.h>
#include <dpp/json.h>


namespace dpp::events {


/**
 * @brief Handle event
 * 
 * @param client Websocket client (current shard)
 * @param j JSON data for the event
 * @param raw Raw JSON string
 */
void presence_update::handle(discord_client* client, json &j, const std::string &raw) {
	if (!client->creator->on_presence_update.empty()) {
		json& d = j["d"];
		dpp::presence_update_t pu(client->owner, client->shard_id, raw);
		pu.rich_presence = dpp::presence().fill_from_json(&d);
		client->creator->queue_work(1, [c = client->creator, pu]() {
			c->on_presence_update.call(pu);
		});
	}
}

};