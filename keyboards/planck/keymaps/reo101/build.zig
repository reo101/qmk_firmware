const std = @import("std");

fn includePaths(step: *std.build.LibExeObjStep, paths: [83][:0]const u8) void {
    for (paths) |path| {
        step.addIncludePath(path);
    }
}

const dirs: [83][:0]const u8 = [_][:0]const u8{
        "../../../../keyboards/planck/keymaps/reo101",
        "../../../../users/reo101",
        "../../../../keyboards/.",
        "../../../../keyboards/.",
        "../../../../keyboards/planck",
        "../../../../keyboards/planck/ez",
        "../../../../keyboards/planck/ez/glow",
        "../../../.././platforms/chibios/boards/GENERIC_STM32_F303XC/configs",
        "../../../../.",
        "../../../../tmk_core",
        "../../../../quantum",
        "../../../../quantum/keymap_extras",
        "../../../../quantum/audio",
        "../../../../quantum/process_keycode",
        "../../../../quantum/sequencer",
        "../../../../drivers",
        "../../../../drivers/eeprom",
        "../../../../quantum/rgb_matrix",
        "../../../../quantum/rgb_matrix/animations",
        "../../../../quantum/rgb_matrix/animations/runners",
        "../../../../drivers/led/issi",
        "../../../../quantum/bootmagic",
        "../../../../.build/obj_planck_ez_glow/src",
        "../../../../.build/obj_planck_ez_glow_reo101/src",
        "../../../../quantum/logging",
        "../../../../lib/printf",
        "../../../../tmk_core/protocol",
        "../../../../platforms",
        "../../../../platforms/chibios",
        "../../../../platforms/chibios/drivers",
        "../../../../tmk_core/protocol",
        "../../../../tmk_core/protocol/chibios",
        "../../../../tmk_core/protocol/chibios/lufa_utils",
        "../../../../lib/chibios/os/license",
        "../../../../lib/chibios/os/oslib/include",
        "../../../../platforms/chibios/boards/GENERIC_STM32_F303XC/configs",
        "../../../../platforms/chibios/boards/common/configs",
        "../../../../keyboards/planck/ez",
        "../../../../lib/chibios/os/common/portability/GCC",
        "../../../../lib/chibios/os/common/startup/ARMCMx/compilers/GCC",
        "../../../../lib/chibios/os/common/startup/ARMCMx/devices/STM32F3xx",
        "../../../../lib/chibios/os/common/ext/ARM/CMSIS/Core/Include",
        "../../../../lib/chibios/os/common/ext/ST/STM32F3xx",
        "../../../../lib/chibios/os/rt/include",
        "../../../../lib/chibios/os/common/portability/GCC",
        "../../../../lib/chibios/os/common/ports/ARM-common",
        "../../../../lib/chibios/os/common/ports/ARMv7-M",
        "../../../../lib/chibios/os/hal/osal/rt-nil",
        "../../../../lib/chibios/os/hal/include",
        "../../../../lib/chibios/os/hal/ports/common/ARMCMx",
        "../../../../lib/chibios/os/hal/ports/STM32/STM32F3xx",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/ADCv3",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/CANv1",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/DACv1",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/DMAv1",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/EXTIv1",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/GPIOv2",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/I2Cv2",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/RTCv2",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/SPIv2",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/SYSTICKv1",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/TIMv1",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/USART",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/USARTv2",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/USBv1",
        "../../../../lib/chibios/os/hal/ports/STM32/LLD/xWDGv1",
        "../../../../lib/chibios/os/hal/boards/ST_STM32F3_DISCOVERY",
        "../../../../lib/chibios/os/hal/lib/streams",
        "../../../../lib/chibios/os/various",
        "../../../../.",
        "../../../../tmk_core",
        "../../../../quantum",
        "../../../../quantum/keymap_extras",
        "../../../../quantum/audio",
        "../../../../quantum/process_keycode",
        "../../../../quantum/sequencer",
        "../../../../drivers",
        "../../../../drivers/eeprom",
        "../../../../quantum/rgb_matrix",
        "../../../../quantum/rgb_matrix/animations",
        "../../../../quantum/rgb_matrix/animations/runners",
        "../../../../drivers/led/issi",
        "../../../../quantum/bootmagic",
};

pub fn build(b: *std.build.Builder) void {
    const target = std.zig.CrossTarget{
        .cpu_arch = .thumb,
        .cpu_model = .{ .explicit = &std.Target.arm.cpu.cortex_m4 },
        .os_tag = .freestanding,
        .abi = .gnueabihf,
    };
    const mode = std.builtin.Mode.ReleaseSmall;

    const keymap: *std.build.LibExeObjStep = b.addObject("keymap", "keymap.zig");
    keymap.setTarget(target);
    keymap.setBuildMode(mode);

    keymap.use_stage1 = true;

    keymap.linkLibC();

    includePaths(keymap, dirs);

    {
        keymap.addIncludeDir("/usr/arm-none-eabi/include");
        keymap.addIncludePath("../../../../keyboards/planck");
        keymap.addIncludePath("../../../../keyboards/planck/ez");
        keymap.addIncludePath("../../../../keyboards/planck/ez/glow");
        keymap.addIncludePath("../../../../.build/obj_planck_ez_glow/src/info_config.h");
        keymap.addIncludePath("../../../../keymaps/reo101");
        keymap.addIncludePath("../../../../platforms/chibios/boards/GENERIC_STM32_F303XC/configs/config.h");
    }

    // lib.linkLibC();

    // _ = obj.installRaw("keymap.o", std.build.InstallRawStep.CreateOptions{
    //    .dest_dir = .{.custom = (".")},
    // });

    const keymap_step = b.step("keymap", "Build the keymap");
    // b.installArtifact(keymap);
    keymap_step.dependOn(&keymap.step);


    const keymap_tests = b.addTest("keymap.zig");
    keymap_tests.setTarget(target);
    keymap_tests.setBuildMode(mode);

    // keymap_tests.addIncludeDir("/data/data/com.termux/files/usr/include");
    keymap_tests.linkLibC();
    keymap_tests.addIncludeDir("../../../../quantum");
    keymap_tests.addIncludeDir("../../../../platforms");
    keymap_tests.addIncludeDir("../../../../keyboards/planck/rev6");
    keymap_tests.addIncludeDir("../../../../tmk_core/protocol");
    keymap_tests.addIncludeDir("../../../../quantum/audio");
    keymap_tests.addIncludeDir("../../../../quantum/logging");
    keymap_tests.addIncludeDir("../../../../quantum/sequencer");

    const keymap_tests_step = b.step("test", "Test keymap");
    keymap_tests_step.dependOn(&keymap_tests.step);

    const layout_tests = b.addTest("layout.zig");
    // layout_tests.setTarget(target);
    // layout_tests.setBuildMode(mode);

    const layout_tests_step = b.step("layout_test", "Test layout()");
    layout_tests_step.dependOn(&layout_tests.step);

    // obj.createObject;
    //
    // std.debug.print("{s}", .{obj.getOutputSource()});
    //
    // const obj_cmd = obj.run();
    //
    // const obj_step = b.step("object", "Build the object");
    // obj_step.dependOn(&obj_cmd.step);
}
