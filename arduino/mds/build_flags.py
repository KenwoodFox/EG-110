import subprocess

revision = (
    subprocess.check_output(
        [
            "git",
            "describe",
            "--abbrev=4",
            "--dirty",
            "--always",
            "--tags",
        ]
    )
    .strip()
    .decode("utf-8")
)
print("-DGIT_REV='\"%s\"'" % revision)
