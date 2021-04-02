# 接受三个参数
# lang=c/c++/undefined
# path=子工程路径
# os=windows/linux

OS_CHARSET != \
	if [ '$(os)' = windows ]; then \
		echo GBK; \
	else \
		echo UTF-8; \
	fi
C_FLAGS = -Wall -g -static -static-libgcc -fexec-charset=$(OS_CHARSET) -std=c11
CXX_FLAGS = -Wall -g -static -static-libgcc -static-libstdc++ -fexec-charset=$(OS_CHARSET) -std=c++17
UNKNOWN_FLAGS = -Wall -g -static -fexec-charset=$(OS_CHARSET)

CC != \
	if [ '$(lang)' = c ]; then \
		echo gcc; \
	elif [ '$(lang)' = c++ ]; then \
		echo g++; \
	else \
		echo cc; \
	fi
FLAGS != \
	if [ '$(lang)' = c ]; then \
		echo $(C_FLAGS); \
	elif [ '$(lang)' = c++ ]; then \
		echo $(CXX_FLAGS); \
	else \
		echo UNKNOWN_FLAGS; \
	fi
SUFFIX != \
	if [ '$(lang)' = c ]; then \
		echo .c; \
	elif [ '$(lang)' = c++ ]; then \
		echo .cpp; \
	else \
		echo UNKNOWN_SUFFIX; \
	fi
OS != \
	if [ '$(os)' = windows ]; then \
		echo win; \
	elif [ '$(os)' = linux ]; then \
		echo linux; \
	else \
		echo UNKNOWN_OS; \
	fi
# 通过 src 的相对位置获取工作空间目录 {/path/to}/src
CUR_DIR = $(shell pwd)
CWD = $(shell echo $(CUR_DIR) | sed 's/\/src.*//g')
# 获取工作空间下的 build 目录
BUILD_DIR = $(CWD)/build
# 从 path 变量获取子工程源文件所在路径
PROJSRC_DIR = $(subst \,/,$(path))
# 获取源文件列表，.c/.cpp 文件
SOURCES := $(shell find $(PROJSRC_DIR) -maxdepth 1 -type f -name '*$(SUFFIX)' -exec basename {} \;)
# 将源文件列表转换为 .o 目标文件列表
OBJECTS := $(patsubst %$(SUFFIX),%.o,$(SOURCES))
# 将源文件列表转换为 build/%.d 依赖推导 fragment（以支持对 .h 的依赖推导），see https://stackoverflow.com/questions/2394609/makefile-header-dependencies
DEPENDS := $(patsubst %.cpp,$(BUILD_DIR)/%.d,$(SOURCES))


# 通过 ".OS_工程目录" 作为名称的标志文件来判断是否仍在编译同一个工程，否则就要删除所有中间和目标文件防止 make 编译出错
PROJNAME = $(shell echo $(PROJSRC_DIR) | sed 's/.*\///')
PROJFLAG_PATH = $(BUILD_DIR)/.$(OS)_$(PROJNAME)
# BUILD_DIR 下没有 PROJNAME 文件则说明第一次编译该工程，必须先清理
EXEC != \
	if [ '$(wildcard $(PROJFLAG_PATH))' = '' ]; then \
		find $(BUILD_DIR) -type f -not -name ".git*" -delete; \
		cd $(BUILD_DIR) && touch .$(OS)_$(PROJNAME); \
	fi


# 默认目标 build/main
# /path/to/build/main: /path/to/build/main.o /path/to/build/dep.o ...
$(BUILD_DIR)/main: $(patsubst %, $(BUILD_DIR)/%, $(OBJECTS))
	$(CC) $(FLAGS) -o $@ $^

# 将依赖推导 fragment (%.o: %.h %.c[pp]) 导入 Makefile
-include $(DEPENDS)
# 制作 .o 中间文件和 .d 依赖推导 fragment 文件
$(BUILD_DIR)/%.o: $(PROJSRC_DIR)/%$(SUFFIX)
	$(CC) $(FLAGS) -MMD -o $@ -c $< -I $(PROJSRC_DIR)


.PHONY: diag clean
diag:
	@echo CC, FLAGS, SUFFIX, OS: $(CC), $(FLAGS), $(SUFFIX), $(OS)
	@echo CUR_DIR, CWD, BUILD_DIR, PROJSRC_DIR: $(CUR_DIR), $(CWD), $(BUILD_DIR), $(PROJSRC_DIR)
	@echo PROJNAME, PROJFLAG_PATH, EXEC: $(PROJNAME), $(PROJFLAG_PATH), $(EXEC)
	@echo SOURCES: $(SOURCES)
	@echo OBJECTS: $(OBJECTS)
	@echo DEPENDS: $(DEPENDS)

clean:
	find $(BUILD_DIR) -type f -not -name ".git*" -delete;
	cd $(CWD) && $(RM) main *.o *.exe;