import datetime


def log_message(level, component, message):
    """
    Generates a log message with a standard format.

    Parameters:
    - level: The log level (e.g., "INFO", "ERROR").
    - component: The component or module generating the log.
    - message: The log message content.
    - context_info: Optional. Additional context information for the log.
    """
    timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    log = f"[{timestamp}] [{level}] [{component}] - {message}"
    print(log)
