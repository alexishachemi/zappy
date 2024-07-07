#!/usr/bin/python3
import sys
import argparse as ap
import logging
import random
from hivemind import Ai, setup_logger

def get_args():
    parser = ap.ArgumentParser(add_help=False)
    parser.add_argument("-help", "--help", action="help", help="Show this help message and exit")
    parser.add_argument("-p", "--port", type=int, help="Port to connect to", required=True)
    parser.add_argument("-h", "--host", type=str, default="0.0.0.0", help="Host to connect to (default: 0.0.0.0)")
    parser.add_argument("-n", "--name", type=str, help="Team name", required=True)
    parser.add_argument("-w", "--wait", action="store_true", help="Wait until a slot opens (default: False)")
    parser.add_argument("-m", "--multip", type=int,
        default=0, help="Maximum number of processes to create excluding the main process. 0 for no multiprocessing (default: 0)")
    parser.add_argument("-l", "--log", type=str, default=None, help="Log file (default: None)")
    parser.add_argument("--log-level", type=str, choices=["debug", "info", "warning", "error", "critical"], default="info", help="Set the logging level (default: info)")
    return parser.parse_args()

def main():
    random.seed()
    args = get_args()
    if args.multip < 0:
        print("Error: Invalid value for -m/--multip. Must be a positive integer")
        return 84
    setup_logger(logging.getLogger())
    logging.getLogger().setLevel(args.log_level.upper())
    if not Ai.run(args.host, args.port, args.name, args.wait, args.multip):
        logging.critical("Failed to start AI")
        return 84
    return 0

if __name__ == "__main__":
    sys.exit(main())
