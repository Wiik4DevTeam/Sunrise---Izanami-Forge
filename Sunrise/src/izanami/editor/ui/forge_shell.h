#pragma once

namespace sunrise::izanami::editor::workspace {
class EditorWorkspace;
}

namespace sunrise::izanami::editor::ui::forge_shell {

/** Draws the standalone, live-world Forge editor shell. */
void draw(workspace::EditorWorkspace& editor) noexcept;

/** @return True while right mouse is held over the live-world viewport. */
[[nodiscard]] bool camera_control_active() noexcept;

/** Clears viewport input state when the shell closes. */
void release_input() noexcept;

} // namespace sunrise::izanami::editor::ui::forge_shell
