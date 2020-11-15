import os
import glob
import json
import argparse
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

class BenchmarkItem:
    def __init__(self, name, time, unit):
        self.name = name
        self.time = time
        self.unit = unit

class Benchmark:
    def __init__(self, name):
        self.name = name
        self.items = []

    def add(self, name, time, unit):
        self.items.append(BenchmarkItem(name, time, unit))

    def size(self):
        return len(self.items)

def create_argument_parser():
    DEFAULT_BENCHMARKS_DIR="./"

    parser = argparse.ArgumentParser(description='Plot Google Benchmark chart')

    parser.add_argument(
        "-b", "--benchmarks-dir",
        default=DEFAULT_BENCHMARKS_DIR, type=str,
        help='Path to Google Benchmark JSON files (default: %(default)s)',
        metavar='BENCHMARKS_DIR', dest='benchmarks_dir'
    )

    return parser

def extract_benchmark_name(filename):
    start = filename.find('/') + 1
    end = filename.find('_benchmark.json')
    return filename[start:end]

def generate_chart(benchmarks):
    labels_count = max([ benchmark.size() for benchmark in benchmarks ])
    x = np.arange(labels_count) # label locations

    bar_width = 0.3

    fig, ax = plt.subplots()

    start_x = x - bar_width

    for benchmark in benchmarks:
        ax.bar(
            start_x,
            [ i.time for i in benchmark.items ],
            width=bar_width, label=benchmark.name
        )
        start_x += bar_width

    ax.set_ylabel(benchmarks[0].items[0].unit)
    ax.set_title('Benchmark')
    ax.set_xticks(x)
    ax.set_xticklabels([ i.name for i in benchmarks[0].items ])
    ax.legend()

    fig.tight_layout()
    plt.show()

if __name__ == "__main__":
    parser = create_argument_parser()
    args = parser.parse_args()

    benchmarks = []

    # process JSON files from the benchmarks directory
    for filename in glob.glob(os.path.join(args.benchmarks_dir, '*_benchmark.json')):
        benchmark = Benchmark(extract_benchmark_name(filename))

        with open(filename, encoding='utf-8', mode='r') as json_file:
            data = json.load(json_file)

            for item in data["benchmarks"]:
                benchmark.add(item["name"], item["real_time"], item["time_unit"])

        benchmarks.append(benchmark)

    generate_chart(benchmarks)
