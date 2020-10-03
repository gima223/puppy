#!/usr/bin/env python
from __future__ import print_function

import sys
import time
# import subprocess
from watchdog.observers import Observer
from watchdog.events import PatternMatchingEventHandler


class MyHandler(PatternMatchingEventHandler):
    def __init__(self,  patterns):
        # patternsで指定したパターンのファイル名を監視を行うクラス
        super(MyHandler, self).__init__(patterns=patterns)

    # def _run_command(self):
        # subprocess.call([self.command, ])

    def on_moved(self, event):
        # self._run_command()
        func_name = sys._getframe().f_code.co_name
        print("Event: {func_name}  {key} {path}".format(
            func_name=func_name, key=event.key, path=event.src_path))

    def on_created(self, event):
        # self._run_command()
        func_name = sys._getframe().f_code.co_name
        print("Event: {func_name}  {key} {path}".format(
            func_name=func_name, key=event.key, path=event.src_path))

    def on_deleted(self, event):
        # self._run_command()
        func_name = sys._getframe().f_code.co_name
        print("Event: {func_name}  {key} {path}".format(
            func_name=func_name, key=event.key, path=event.src_path))

    def on_modified(self, event):
        func_name = sys._getframe().f_code.co_name
        print("Event: {func_name}  {key} {path}".format(
            func_name=func_name, key=event.key, path=event.src_path))


def watch(path):
    # pathで指定したディレクトリの監視を行う
    event_handler = MyHandler(["*"])
    observer = Observer()
    observer.schedule(event_handler, path, recursive=True)
    observer.start()
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()


if __name__ == "__main__":
    if 2 > len(sys.argv):
        print("Usage:", sys.argv[0], "dir_to_watch")
    else:
        print("Watchdog start!! ", sys.argv[1:])
        watch(sys.argv[1])
